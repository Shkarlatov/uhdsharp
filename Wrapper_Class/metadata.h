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

This file uses UHD library from Ettus Research LLC
Copyright 2010-2012,2014 Ettus Research LLC under GNU General Public License http://www.gnu.org/licenses

*******************************************************************************/

#pragma once

#include <uhd/types/metadata.hpp>
#include <uhd/types/time_spec.hpp>

#include "helper.h"

#include <string>

namespace UHD_SHARP
{
	public ref class rx_metadata_t
	{
	private:
		uhd::rx_metadata_t* _md;

	public:
		// Allocate the native object on the C++ Heap via a constructor
		rx_metadata_t() : _md(new uhd::rx_metadata_t) {}
		// Copy constructor
		rx_metadata_t(uhd::rx_metadata_t oldCopy) : _md(new uhd::rx_metadata_t)
		{
			_md->end_of_burst = oldCopy.end_of_burst;
			_md->error_code = oldCopy.error_code;
			_md->fragment_offset = oldCopy.fragment_offset;
			_md->has_time_spec = oldCopy.has_time_spec;
			_md->more_fragments = oldCopy.more_fragments;
			_md->out_of_sequence = oldCopy.out_of_sequence;
			_md->start_of_burst = oldCopy.start_of_burst;
			//_md->time_spec = new uhd::time_spec_t()*; //TODO
		}

		// Deallocate the native object on a destructor
		~rx_metadata_t() {
			delete _md;
		}

	protected:
		// Deallocate the native object on the finalizer just in case no destructor is called
		!rx_metadata_t() {
			delete _md;
		}

	public:

		//! Reset values.
		void reset() { _md->reset(); }

		//! Has time specification?
		property bool has_time_spec
		{
			bool get(){ return _md->has_time_spec; }
			void set(bool val){ _md->has_time_spec = val; }
		}

		//! Time of the first sample.
		property uhd::time_spec_t* time_spec
		{
			uhd::time_spec_t* get(){ return &(_md->time_spec); }
			void set(uhd::time_spec_t* val){ _md->time_spec = *val; }
		}

		/*!
		* Fragmentation flag:
		* Similar to IPv4 fragmentation: http://en.wikipedia.org/wiki/IPv4#Fragmentation_and_reassembly
		* More fragments is true when the input buffer has insufficient size to fit
		* an entire received packet. More fragments will be false for the last fragment.
		*/
		property bool more_fragments
		{
			bool get(){ return _md->more_fragments; }
			void set(bool val){ _md->more_fragments = val; }
		}

		/*!
		* Fragmentation offset:
		* The fragment offset is the sample number at the start of the receive buffer.
		* For non-fragmented receives, the fragment offset should always be zero.
		*/
		property int fragment_offset
		{
			int get(){ return _md->fragment_offset; }
			void set(int val){ _md->fragment_offset = val; }
		}

		//! Start of burst will be true for the first packet in the chain.
		property bool start_of_burst
		{
			bool get(){ return _md->start_of_burst; }
			void set(bool val){ _md->start_of_burst = val; }
		}


		//! End of burst will be true for the last packet in the chain.
		property bool end_of_burst
		{
			bool get(){ return _md->end_of_burst; }
			void set(bool val){ _md->end_of_burst = val; }
		}


		/*!
		* The error condition on a receive call.
		*
		* Note: When an overrun occurs in continuous streaming mode,
		* the device will continue to send samples to the host.
		* For other streaming modes, streaming will discontinue
		* until the user issues a new stream command.
		*
		* The metadata fields have meaning for the following error codes:
		* - none
		* - late command
		* - broken chain
		* - overflow
		*/
		enum class error_code_t {
			//! No error associated with this metadata.
			ERROR_CODE_NONE = uhd::rx_metadata_t::ERROR_CODE_NONE,
			//! No packet received, implementation timed-out.
			ERROR_CODE_TIMEOUT = uhd::rx_metadata_t::ERROR_CODE_TIMEOUT,
			//! A stream command was issued in the past.
			ERROR_CODE_LATE_COMMAND = uhd::rx_metadata_t::ERROR_CODE_LATE_COMMAND,
			//! Expected another stream command.
			ERROR_CODE_BROKEN_CHAIN = uhd::rx_metadata_t::ERROR_CODE_BROKEN_CHAIN,
			/*!
			* An internal receive buffer has filled or a sequence error has been detected.
			* So, why is this overloaded?  Simple: legacy support. It would have been much cleaner
			* to create a separate error code for a sequence error, but that would have broken
			* legacy applications.  So, the out_of_sequence flag was added to differentiate between
			* the two error cases.  In either case, data is missing between this time_spec and the
			* and the time_spec of the next successful receive.
			*/
			ERROR_CODE_OVERFLOW = uhd::rx_metadata_t::ERROR_CODE_OVERFLOW,
			//! Multi-channel alignment failed.
			ERROR_CODE_ALIGNMENT = uhd::rx_metadata_t::ERROR_CODE_ALIGNMENT,
			//! The packet could not be parsed.
			ERROR_CODE_BAD_PACKET = uhd::rx_metadata_t::ERROR_CODE_BAD_PACKET
		};

		property error_code_t error_code
		{
			error_code_t get(){ return (error_code_t)_md->error_code; }
			void set(error_code_t val){ _md->error_code = (uhd::rx_metadata_t::error_code_t)val; }

		}

		//! Out of sequence.  The transport has either dropped a packet or received data out of order.
		property bool out_of_sequence
		{
			bool get(){ return _md->out_of_sequence; }
			void set(bool val){ _md->out_of_sequence = val; }
		}

		/*!
		* Convert a rx_metadata_t into a pretty print string.
		*
		* \param compact Set to false for a more verbose output.
		* \return a printable string representing the metadata.
		*/
		String^ to_pp_string(){ return helper::UnmanagedStringToManaged(_md->to_pp_string()); }

		/*!
		* Convert a rx_metadata_t into a pretty print string.
		*
		* \param compact Set to false for a more verbose output.
		* \return a printable string representing the metadata.
		*/
		String^ to_pp_string(bool compact) { return helper::UnmanagedStringToManaged(_md->to_pp_string(compact)); }

		/*!
		* Similar to C's strerror() function, creates a std::string describing the error code.
		* \return a printable string representing the error.
		*/
		String^ strerror(void) { return helper::UnmanagedStringToManaged(_md->strerror()); }

		uhd::rx_metadata_t* get(){ return _md; }
	};
}