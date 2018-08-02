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

#include "helper.h" 
#include <uhd/types/device_addr.hpp>
#include <string>

using namespace System;

namespace UHD_SHARP {

	public ref class device_addr_t
	{

	private:
		uhd::device_addr_t *_device_addr_t;

	public:
		device_addr_t(String ^args)
		{
			_device_addr_t = new uhd::device_addr_t(helper::MarshalString(args));
		}

		device_addr_t(std::string args)
		{
			_device_addr_t = new uhd::device_addr_t(args);
		}

		~device_addr_t()
		{
			delete _device_addr_t;
			_device_addr_t = 0;
		}

		String^ to_pp_string(void)
		{
			return helper::UnmanagedStringToManaged(_device_addr_t->to_pp_string());
		}

		String^ to_string(void)
		{
			return helper::UnmanagedStringToManaged(_device_addr_t->to_string());
		}

	};

	typedef cli::array<device_addr_t^> device_addrs_t;
}