// Based on http://stackoverflow.com/questions/14802876/what-is-a-good-way-to-direct-console-output-to-text-box-in-windows-form
// More info can be found here: http://msdn.microsoft.com/en-us/library/system.console.setout(v=vs.110).aspx

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WrapperDemo
{
    public class TextBoxWriter : TextWriter
    {
        TextBox _output = null;

        public TextBoxWriter(TextBox output)
        {
            _output = output;
        }

        public override void Write(char value)
        {
            base.Write(value);
            _output.AppendText(value.ToString());
        }

        public override Encoding Encoding
        {
            get { return System.Text.Encoding.UTF8; }
        }
    }
}
