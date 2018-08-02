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

#include "helper.h"

#include <uhd/version.hpp>
#include <string>

using namespace System;

namespace UHD_SHARP{

	public ref class version{

	public:
		//! Get the version string (dotted version number + build info)
		//UHD_API std::string get_version_string(void);
		static String ^get_version_string()
		{
			return helper::UnmanagedStringToManaged(uhd::get_version_string());
		}

		//! Get the ABI compatibility string for this build of the library
		//UHD_API std::string get_abi_string(void);
		static String ^ get_abi_string()
		{
			return helper::UnmanagedStringToManaged(uhd::get_abi_string());
		}
	};
} 
