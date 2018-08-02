/*******************************************************************************

Copyright(c) 2014 Nir Eden, 4Z7DEF  https://uhdsharp.codeplex.com/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

This file uses UHD library from Ettus Research LLC https://github.com/EttusResearch/uhd
Copyright 2010-2012,2014 Ettus Research LLC under GNU General Public License http://www.gnu.org/licenses

*******************************************************************************/

#pragma once

#include <iostream>       // std::cout
#include "unmanaged_pointer_holder.h"

using namespace System::Threading;

#define NUMBERS_OF_BUFFERS (2)
#define RX_BUFFER_SIZE (100000)

namespace UHD_SHARP {

#pragma managed

	delegate void DataReceivedCallbackDelegate(array<int>^ real, array<int>^ imaginary, int length);
	public delegate void RXEvent(array<int>^ real, array<int>^ imaginary, int length, rx_metadata_t^ md);

	std::array< std::vector<std::complex<short>>, 2> bufferVector; // Double buffer for RX data
	std::array<int, 2> RXDataLength; // Double buffer for RX data length

	int currentRXBuffer = 0;

	private ref class RXCopy
	{
	private:
		DataReceivedCallbackDelegate^ _DataReceived;

	public:
		RXCopy(DataReceivedCallbackDelegate^ NewDataReceived)
		{
			_DataReceived = NewDataReceived;
		}

		void DoRXCopy()
		{
			array<array<int>^>^ real = gcnew array<array<int>^>(2){
				gcnew array< int >(RX_BUFFER_SIZE), gcnew array< int >(RX_BUFFER_SIZE)
			};
			array<array<int>^>^ imaginary = gcnew array<array<int>^>(2){
				gcnew array< int >(RX_BUFFER_SIZE), gcnew array< int >(RX_BUFFER_SIZE)
			};

			int dataCopyID = 0;
			int dataProcessID = 1;
			int currentDataBuffer; //Double buffer ID to read from
			int count; // General counter in for loops
			while (true)
			{
				try
				{
					Thread::Sleep(Timeout::Infinite); // Sleep untile next iteration
				}
				catch (ThreadInterruptedException^ /*e*/)
				{
					if (dataCopyID == 1)
					{
						dataCopyID = 0;
						dataProcessID = 1;
					}
					else
					{
						dataCopyID = 1;
						dataProcessID = 0;
					}


					currentDataBuffer = currentRXBuffer ^ 1;

					for (count = RXDataLength[currentDataBuffer]; count--;)
					{
						real[dataCopyID][count] = bufferVector[currentDataBuffer][count].real();
						imaginary[dataCopyID][count] = bufferVector[currentDataBuffer][count].imag();
					}
					_DataReceived(real[dataProcessID], imaginary[dataProcessID], RXDataLength[currentDataBuffer]);
				}

			}
		}

	};

	private ref class RXCollect
	{
	private:
		usrp_holder* _usrp;

		bool _isRunning;// = false;
		bool _stopRX = false;
		DataReceivedCallbackDelegate^ _DataReceived;// = nullptr;

		rx_stream_holder* _rx_stream;// = nullptr;

	public:
		RXCollect(usrp_holder* usrp/*, int spb*/, DataReceivedCallbackDelegate^ NewDataReceived)//,Thread^ CopyAndFireThread)
		{
			_isRunning = false;
			_stopRX = false;

			_usrp = usrp;
			//bufferSize = spb;
			_DataReceived = NewDataReceived;

			//create a receive streamer
			uhd::stream_args_t stream_args("sc16", "sc16");
			//uhd::rx_streamer::sptr _rx_stream = _usrp->get()->get_rx_stream(stream_args);
			_rx_stream = new rx_stream_holder(_usrp, stream_args);

			// Populate RX data double buffer
			for (int count = bufferVector.size(); count--;)
				bufferVector[count] = std::vector<std::complex<short>>(RX_BUFFER_SIZE);

		}

		void DoRXCollect()
		{
			if (_isRunning)
				return;
			_isRunning = true;
			_stopRX = false;

			uhd::rx_metadata_t md;

			RXCopy^ _CopyAndFire = gcnew RXCopy(_DataReceived);
			Thread^ _CopyAndFireThread = gcnew Thread(gcnew ThreadStart(_CopyAndFire, &RXCopy::DoRXCopy));
			_CopyAndFireThread->Priority = ThreadPriority::BelowNormal;
			_CopyAndFireThread->Start();

			// Calculating # of packets in single RX buffer
			size_t num_rx_samps;
			int max_num_samps = _rx_stream->get()->get_max_num_samps();
			int samps_per_buffer = RX_BUFFER_SIZE / max_num_samps;

			// Initiating counters
			int num_rx_samps_in_buffer = 0;
			int count = 0;
			currentRXBuffer=0;

			// Starting RX
			_rx_stream->start();

			// Run RX
			while (!_stopRX)
			{
				num_rx_samps_in_buffer = 0;

				for (count = samps_per_buffer; count--;)
				{
					num_rx_samps = _rx_stream->get()->recv(&bufferVector[currentRXBuffer][num_rx_samps_in_buffer], max_num_samps, md, 3.0, false);
					num_rx_samps_in_buffer += num_rx_samps;
					if (md.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW)
					{
						
						std::cout << "O";
					}
				}
				RXDataLength[currentRXBuffer] = num_rx_samps_in_buffer;

				// Toggle double buffer ID
				currentRXBuffer ^= 1;

				_CopyAndFireThread->Interrupt();
			}

			_rx_stream->stop();
			System::Threading::Thread::Sleep(250);

			std::cout << std::endl << "### Stopped ###" << std::endl;
			_CopyAndFireThread->Abort();
			_CopyAndFireThread->Join(1000);

			_isRunning = false;
			_stopRX = false;
		}

		void StopRX()
		{
			_stopRX = true;
		}

		bool IsRunning()
		{
			return _isRunning;
		}

		virtual event RXEvent^ DataReceiverEvent;
	};
}