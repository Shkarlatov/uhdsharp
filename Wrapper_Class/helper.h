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

*******************************************************************************/

#pragma once

#include <string>

using namespace System;
using namespace System::Runtime::InteropServices;

namespace UHD_SHARP
{
	private ref class helper
	{
	public:
		static std::string MarshalString(String ^ s)
		{
			using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
			return os;
		}

		static String ^UnmanagedStringToManaged(std::string input_string)
		{
			return gcnew String(input_string.c_str());
		}

		[DllImport("kernel32.dll",
			EntryPoint = "AllocConsole",
			SetLastError = true,
			CharSet = CharSet::Auto,
			CallingConvention = CallingConvention::StdCall)]
		static int AllocConsole();

		// Source: https://social.msdn.microsoft.com/Forums/en-US/b7a14400-6d72-4fbf-9927-0966f69ef4a2/how-to-open-console-window-in-windows-apllication?forum=csharplanguage
		static const int STD_OUTPUT_HANDLE = -11;
		static const int MY_CODE_PAGE = 437;

		/// Return Type: HANDLE->void*
		///nStdHandle: DWORD->unsigned int
		[DllImportAttribute("kernel32.dll", EntryPoint = "GetStdHandle")]
		static System::IntPtr GetStdHandle(Int32 nStdHandle);

		/*/// Return Type: BOOL->int
		[DllImportAttribute("kernel32.dll", EntryPoint = "AllocConsole")]
		[return:MarshalAsAttribute(UnmanagedType::Bool)]
		static bool AllocConsole();*/

	};

}