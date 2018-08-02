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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UHD_SHARP;

namespace uhd_sharp_find_devices
{
    class Program
    {
        static void Main(string[] args)
        {
            UHD_SHARP.device_addr_t[] devices = device.find("");
            Console.WriteLine("Using uhd.dll version " + version.get_version_string());
            foreach (UHD_SHARP.device_addr_t single_device in devices)
                Console.WriteLine(single_device.to_pp_string());
            Console.WriteLine("Press any key exit");
            Console.ReadKey();
        }
    }
}
