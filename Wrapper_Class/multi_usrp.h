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

#define GETTER(FTYPE,FNAME) FTYPE FNAME() { return (_usrp->get())->FNAME(); }
#define GETTER_DEFAULT(FTYPE,FNAME,OPTIONALTYPE,OPTIONALVARNAME) FTYPE FNAME() { return (_usrp->get())->FNAME(); } FTYPE FNAME(OPTIONALTYPE OPTIONALVARNAME) { return (_usrp->get())->FNAME(OPTIONALVARNAME); }
#define STRING_GETTER(X) String^ X() { return helper::UnmanagedStringToManaged((_usrp->get())->X()); }
#define STRING_GETTER_DEFAULT(FNAME,OPTIONALTYPE,OPTIONALVARNAME) String^ FNAME() { return helper::UnmanagedStringToManaged((_usrp->get())->FNAME()); } String^ FNAME(OPTIONALTYPE OPTIONALVARNAME) { return helper::UnmanagedStringToManaged((_usrp->get())->FNAME(OPTIONALVARNAME)); }
#define SETTER(X,Y) X(Y val) { (_usrp->get())->X(val) }
#define SETTER_DEFAULT(FNAME,VARTYPE,VARNAME,OPTIONALTYPE,OPTIONALVARNAME) void FNAME(VARTYPE VARNAME) { (_usrp->get())->FNAME(VARNAME); } void FNAME(VARTYPE VARNAME, OPTIONALTYPE OPTIONALVARNAME) { (_usrp->get())->FNAME(VARNAME,OPTIONALVARNAME); }
#define STRING_SETTER(FNAME,VARNAME) void FNAME(String^ VARNAME) { (_usrp->get())->FNAME(helper::MarshalString(VARNAME) ); }
#define STRING_SETTER_DEFAULT(FNAME,VARNAME,OPTIONALTYPE,OPTIONALVARNAME) void FNAME(String^ VARNAME) { (_usrp->get())->FNAME(helper::MarshalString(VARNAME) ); } void FNAME(String^ VARNAME, OPTIONALTYPE OPTIONALVARNAME) { (_usrp->get())->FNAME(helper::MarshalString(VARNAME),OPTIONALVARNAME) ; }


#include <uhd/usrp/multi_usrp.hpp>

#include "helper.h"
#include "metadata.h"
#include "Files.h"
#include "unmanaged_pointer_holder.h"
#include "RX.h"
#include <string>
#include <iostream>       // std::cout

using namespace System;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Numerics;

namespace UHD_SHARP {

#pragma managed

	public ref class multi_usrp
	{
	public:
		property bool isConnected {
			bool get()
			{
				return _isConnected;
			}
		};

	private:
		usrp_holder* _usrp; // usrp pointer
		RXCollect^ _RX = nullptr; // Pointer to RXCollect thread
		bool _isConnected = false; // Is connected to multi-usrp?

		void connect(String ^ args, String ^ subdev)
		{
			CheakFilesTree(); // Extractind uhd.dll if needed
			try
			{
				// Create new multi_usrp
				_usrp = new usrp_holder(helper::MarshalString(args));
				
				// Lock mboard clocks
				(_usrp->get())->set_clock_source("internal");

				// Always select the subdevice first, the channel mapping affects the other settings
				(_usrp->get())->set_rx_subdev_spec(helper::MarshalString(subdev));

			}
			catch (std::exception& e)
			{
				std::cout << "Cannot open USRP: " << e.what() << std::endl;
				_usrp = nullptr;
				_isConnected = false;
				return;
			}
			
			_isConnected = true;
		}

	protected:
		// Deallocate the native object on the finalizer just in case no destructor is called
		!multi_usrp() {
			if (_RX != nullptr)
				_RX->StopRX();
			//delete usrp;
			delete _usrp;
		}

	public:
		// Allocate the native object on the C++ Heap via a constructor
		multi_usrp()
		{
			connect("", "");
		}

		multi_usrp(String ^ args)
		{
			connect(args, "");
		}

		multi_usrp(String ^ args, String ^ subdev)
		{
			connect(args, subdev);
		}

		// Deallocate the native object on a destructor
		~multi_usrp()
		{
			if (_RX != nullptr)
				_RX->StopRX();
			delete _usrp;
			_usrp = nullptr;
		}

		//virtual void set_master_clock_rate(double rate, size_t mboard = ALL_MBOARDS) = 0;
		SETTER_DEFAULT(set_master_clock_rate,double, rate, int, mboard)

		//virtual double get_master_clock_rate(size_t mboard = 0) = 0;
		GETTER_DEFAULT(double,get_master_clock_rate,int,mboard)

		STRING_GETTER(get_pp_string)
		//String^ get_pp_string(void) { return helper::UnmanagedStringToManaged((_usrp->get())->get_pp_string());}

		//virtual std::string get_mboard_name(size_t mboard = 0) = 0;
		STRING_GETTER_DEFAULT(get_mboard_name, int, mboard)

		//virtual time_spec_t get_time_now(size_t mboard = 0) = 0;

		//virtual time_spec_t get_time_last_pps(size_t mboard = 0) = 0;

		//virtual void set_time_now(const time_spec_t &time_spec, size_t mboard = ALL_MBOARDS) = 0;

		//virtual void set_time_next_pps(const time_spec_t &time_spec, size_t mboard = ALL_MBOARDS) = 0;

		//virtual void set_time_unknown_pps(const time_spec_t &time_spec) = 0;

		//virtual bool get_time_synchronized(void) = 0;
		GETTER(bool,get_time_synchronized)

		//virtual void set_command_time(const uhd::time_spec_t &time_spec, size_t mboard = ALL_MBOARDS) = 0;

		//virtual void clear_command_time(size_t mboard = ALL_MBOARDS) = 0;
		void clear_command_time(){ (_usrp->get())->clear_command_time(); } void clear_command_time(int mboard){ (_usrp->get())->clear_command_time(mboard); }

		//virtual void issue_stream_cmd(const stream_cmd_t &stream_cmd, size_t chan = ALL_CHANS) = 0;

		//virtual void set_clock_config(const clock_config_t &clock_config, size_t mboard = ALL_MBOARDS) = 0;

		//virtual void set_time_source(const std::string &source, const size_t mboard = ALL_MBOARDS) = 0;
		STRING_SETTER_DEFAULT(set_time_source, source, int, mboard)

		//virtual std::string get_time_source(const size_t mboard) = 0;
		String^ get_time_source(int mboard) { return helper::UnmanagedStringToManaged((_usrp->get())->get_time_source(mboard)); }

		//virtual std::vector<std::string> get_time_sources(const size_t mboard) = 0;
		array<String^>^ get_time_sources(int mboard)
		{
			std::vector<std::string> strout = (_usrp->get())->get_time_sources(mboard);
			array<String^>^ retval = gcnew array<String^>(strout.size());
			for (unsigned i = 0; i < strout.size(); i++)
				retval[i] = gcnew String(helper::UnmanagedStringToManaged(strout[i]));
		
			return retval;
		}


		//virtual void set_clock_source(const std::string &source, const size_t mboard = ALL_MBOARDS) = 0;
		STRING_SETTER_DEFAULT(set_clock_source,source,int,mboard)

		//virtual std::string get_clock_source(const size_t mboard) = 0;
		String^ get_clock_source(int mboard) { return helper::UnmanagedStringToManaged((_usrp->get())->get_clock_source(mboard)); }

		//virtual std::vector<std::string> get_clock_sources(const size_t mboard) = 0;
		array<String^>^ get_clock_sources(int mboard)
		{
			std::vector<std::string> strout = (_usrp->get())->get_clock_sources(mboard);
			array<String^>^ retval = gcnew array<String^>(strout.size());
			for (unsigned i = 0; i < strout.size(); i++)
				retval[i] = gcnew String(helper::UnmanagedStringToManaged(strout[i]));

			return retval;
		}
		
		//virtual void set_clock_source_out(const bool enb, const size_t mboard = ALL_MBOARDS) = 0;
		SETTER_DEFAULT(set_clock_source_out, bool, enb, int, mboard)

		//virtual void set_time_source_out(const bool enb, const size_t mboard = ALL_MBOARDS) = 0;
		SETTER_DEFAULT(set_time_source_out, bool, enb, int, mboard)

		//virtual size_t get_num_mboards(void) = 0;
		GETTER(int, get_num_mboards)

		//virtual sensor_value_t get_mboard_sensor(const std::string &name, size_t mboard = 0) = 0;

		//virtual std::vector<std::string> get_mboard_sensor_names(size_t mboard = 0) = 0;
		array<String^>^ get_mboard_sensor_names(){ return get_mboard_sensor_names(0); }
		array<String^>^ get_mboard_sensor_names(int mboard)
		{
			std::vector<std::string> strout = (_usrp->get())->get_mboard_sensor_names(mboard);
			array<String^>^ retval = gcnew array<String^>(strout.size());
			for (unsigned i = 0; i < strout.size(); i++)
				retval[i] = gcnew String(helper::UnmanagedStringToManaged(strout[i]));

			return retval;
		}


		//virtual void set_user_register(const boost::uint8_t addr, const boost::uint32_t data, size_t mboard = ALL_MBOARDS) = 0;

		// RX methods

		//virtual void set_rx_subdev_spec(const uhd::usrp::subdev_spec_t &spec, size_t mboard = ALL_MBOARDS) = 0;
		STRING_SETTER_DEFAULT(set_rx_subdev_spec, spec, int, mboard)

		//virtual uhd::usrp::subdev_spec_t get_rx_subdev_spec(size_t mboard = 0) = 0;

		GETTER(int,get_rx_num_channels)
		//virtual size_t get_rx_num_channels(void) = 0;

		STRING_GETTER_DEFAULT(get_rx_subdev_name, int, chan)
		//virtual std::string get_rx_subdev_name(size_t chan = 0) = 0;

		SETTER_DEFAULT(set_rx_rate, double, rate,int,chan)
		//virtual void set_rx_rate(double rate, size_t chan = ALL_CHANS) = 0;

		GETTER_DEFAULT(double, get_rx_rate,int,chan)
		//virtual double get_rx_rate(size_t chan = 0) = 0;

		//virtual meta_range_t get_rx_rates(size_t chan = 0) = 0;

		//virtual tune_result_t set_rx_freq(
		//	const tune_request_t &tune_request, size_t chan = 0
		//	) = 0;
		void set_rx_freq(double freq,bool _int_n){
			uhd::tune_request_t tune_request(freq);
			if (_int_n)
				tune_request.args = uhd::device_addr_t("mode_n=integer");
			(_usrp->get())->set_rx_freq(tune_request);
		}
		void set_rx_freq(double freq){
			set_rx_freq(freq, false);
		}

		//virtual double get_rx_freq(size_t chan = 0) = 0;
		GETTER_DEFAULT(double,get_rx_freq,int,chan)

		//virtual freq_range_t get_rx_freq_range(size_t chan = 0) = 0;

		//virtual freq_range_t get_fe_rx_freq_range(size_t chan = 0) = 0;

		//virtual void set_rx_gain(double gain, const std::string &name, size_t chan = 0) = 0;

		//void set_rx_gain(double gain, size_t chan = 0){
		//	return this->set_rx_gain(gain, ALL_GAINS, chan);
		//}
		SETTER_DEFAULT(set_rx_gain,double,gain,int,chan)
		
		//virtual double get_rx_gain(const std::string &name, size_t chan = 0) = 0;

		GETTER_DEFAULT(double, get_rx_gain,int,chan)
		//double get_rx_gain(size_t chan = 0){
		//	return this->get_rx_gain(ALL_GAINS, chan);
		//}

		//virtual gain_range_t get_rx_gain_range(const std::string &name, size_t chan = 0) = 0;

		//gain_range_t get_rx_gain_range(size_t chan = 0){
		//	return this->get_rx_gain_range(ALL_GAINS, chan);
		//}

		//virtual std::vector<std::string> get_rx_gain_names(size_t chan = 0) = 0;
		array<String^>^ get_rx_gain_names(){ return get_rx_gain_names(0); }
		array<String^>^ get_rx_gain_names(int mboard)
		{
			std::vector<std::string> strout = (_usrp->get())->get_rx_gain_names(mboard);
			array<String^>^ retval = gcnew array<String^>(strout.size());
			for (unsigned i = 0; i < strout.size(); i++)
				retval[i] = gcnew String(helper::UnmanagedStringToManaged(strout[i]));

			return retval;
		}

		//virtual void set_rx_antenna(const std::string &ant, size_t chan = 0) = 0;
		STRING_SETTER_DEFAULT(set_rx_antenna,ant,int,chan)

		//virtual std::string get_rx_antenna(size_t chan = 0) = 0;
		STRING_GETTER_DEFAULT(get_rx_antenna,int,chan)

		//virtual std::vector<std::string> get_rx_antennas(size_t chan = 0) = 0;
		array<String^>^ get_rx_anntenas(int chan)
		{
			std::vector<std::string> strout = (_usrp->get())->get_rx_antennas(chan);
			array<String^>^ retval = gcnew array<String^>(strout.size());
			for (unsigned i = 0; i < strout.size(); i++)
				retval[i] = gcnew String(helper::UnmanagedStringToManaged(strout[i]));
		
			return retval;
		}

		array<String^>^ get_rx_anntenas() {
			return get_rx_anntenas(0);
		}

		//UHD_DEPRECATED bool get_rx_lo_locked(size_t chan = 0){
		//	return this->get_rx_sensor("lo_locked", chan).to_bool();
		//}
		//GETTER_DEFAULT(bool, get_rx_lo_locked,int,chan)

		//virtual void set_rx_bandwidth(double bandwidth, size_t chan = 0) = 0;
		SETTER_DEFAULT(set_rx_bandwidth,double,bandwidth,int,chan)

		//virtual double get_rx_bandwidth(size_t chan = 0) = 0;
		GETTER_DEFAULT(double, get_rx_bandwidth,int,chan)

		//virtual meta_range_t get_rx_bandwidth_range(size_t chan = 0) = 0;

		//UHD_DEPRECATED double read_rssi(size_t chan = 0){
		//	return this->get_rx_sensor("rssi", chan).to_real();
		//}

		//virtual dboard_iface::sptr get_rx_dboard_iface(size_t chan = 0) = 0;

		//virtual sensor_value_t get_rx_sensor(const std::string &name, size_t chan = 0) = 0;

		//virtual std::vector<std::string> get_rx_sensor_names(size_t chan = 0) = 0;
		array<String^>^ get_rx_sensor_names(){ return get_rx_gain_names(0); }
		array<String^>^ get_rx_sensor_names(int mboard)
		{
			std::vector<std::string> strout = (_usrp->get())->get_rx_sensor_names(mboard);
			array<String^>^ retval = gcnew array<String^>(strout.size());
			for (unsigned i = 0; i < strout.size(); i++)
				retval[i] = gcnew String(helper::UnmanagedStringToManaged(strout[i]));

			return retval;
		}


		//virtual void set_rx_dc_offset(const bool enb, size_t chan = ALL_CHANS) = 0;
		SETTER_DEFAULT(set_rx_dc_offset,bool,enb,int,chan)

		//virtual void set_rx_dc_offset(const std::complex<double> &offset, size_t chan = ALL_CHANS) = 0;
		void set_rx_dc_offset(double real, double imaginary){ set_rx_dc_offset(real, imaginary, uhd::usrp::multi_usrp::ALL_CHANS); }
		void set_rx_dc_offset(double real, double imaginary, int chan)
		{
			(_usrp->get())->set_rx_dc_offset(std::complex<double>(real, imaginary), chan);
		}

		//virtual void set_rx_iq_balance(const std::complex<double> &correction, size_t chan = ALL_CHANS) = 0;
		void set_rx_iq_balance(double real, double imaginary){ set_rx_dc_offset(real, imaginary, uhd::usrp::multi_usrp::ALL_CHANS); }
		void set_rx_iq_balance(double real, double imaginary, int chan)
		{
			(_usrp->get())->set_rx_iq_balance(std::complex<double>(real, imaginary), chan);
		}

		// Start RX procedure and fire OnDataReceived events
		int begin_rx_stream()
		{			
			System::Diagnostics::Process^ myProcess = System::Diagnostics::Process::GetCurrentProcess();
			myProcess->PriorityClass = System::Diagnostics::ProcessPriorityClass::RealTime;

			if (_RX == nullptr)
			{
				DataReceivedCallbackDelegate^ DR = gcnew DataReceivedCallbackDelegate(this, &multi_usrp::OnDataReceived);

				_RX = gcnew RXCollect(_usrp, DR);
			}

			if (_RX->IsRunning())
				return -1;
			

			ThreadStart^ threadDelegate = gcnew ThreadStart(_RX, &RXCollect::DoRXCollect);
			Thread^ RXThread = gcnew Thread(threadDelegate);
			RXThread->Priority = ThreadPriority::BelowNormal; // AboveNormal;
			RXThread->Start();
			
			return 0;
		}

		// Stops running RX process
		void stop_rx_stream()
		{
			if (_RX != nullptr)
			{
				_RX->StopRX();
			}
		}

		// Data received and copied callback
		void OnDataReceived(array<int>^ real, array<int>^ imaginary, int length)
		{
			DataReceiverEvent(real, imaginary, length,gcnew UHD_SHARP::rx_metadata_t());
		}

		bool IsRXRunning()
		{
			if (_RX == nullptr)
				return false;
			else
				return _RX->IsRunning();
		}

		virtual event RXEvent^ DataReceiverEvent;

	};
}