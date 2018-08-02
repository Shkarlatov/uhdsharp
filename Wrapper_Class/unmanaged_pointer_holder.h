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

#include <uhd/usrp/multi_usrp.hpp>

namespace UHD_SHARP {

#pragma unmanaged

	// Holds pointer to uhd::usrp::multi_usrp instance
	private class usrp_holder
	{
	public:
		usrp_holder(std::string args) :_usrp(0)
		{
			_usrp = uhd::usrp::multi_usrp::make(args);
			std::cout << "Multi_usrp created" << std::endl;
		}

		~usrp_holder()
		{
			_usrp.reset();
		}

		uhd::usrp::multi_usrp::sptr get()
		{
			return _usrp;
		}

	private:
		uhd::usrp::multi_usrp::sptr _usrp;
	};

	// Holds pointer to uhd::rx_streamer instance
	private class rx_stream_holder
	{
	public:
		rx_stream_holder(usrp_holder* usrp, uhd::stream_args_t stream_args) //:_rx_stream(0)
		{
			_rx_stream = usrp->get()->get_rx_stream(stream_args);
		}

		// Deallocate the native object on a destructor
		~rx_stream_holder()
		{
			_rx_stream.reset();
		}

		uhd::rx_streamer::sptr get()
		{
			return _rx_stream;
		}

		void start()
		{
			// Setup stream
			uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
			stream_cmd.stream_now = true;
			stream_cmd.time_spec = uhd::time_spec_t();
			_rx_stream->issue_stream_cmd(stream_cmd);
		}

		void stop()
		{
			uhd::stream_cmd_t stream_cmd_stop(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
			stream_cmd_stop.stream_now = false;
			stream_cmd_stop.time_spec = uhd::time_spec_t();
			_rx_stream->issue_stream_cmd(stream_cmd_stop);
		}

	private:
		uhd::rx_streamer::sptr _rx_stream;
	};


}