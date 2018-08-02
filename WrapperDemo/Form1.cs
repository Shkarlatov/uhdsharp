
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

This file uses AForge.NET framework http://www.aforgenet.com/framework/ under LGPL v3 license http://www.gnu.org/licenses/lgpl.html
Copyright © Andrew Kirillov, 2005-2009 andrew.kirillov@aforgenet.com

*******************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Numerics;

using UHD_SHARP;
using AForge.Math;
using AForge.Controls;
using System.Runtime.InteropServices;

namespace WrapperDemo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        multi_usrp usrp;
         
        // Chart:
        const int numberOfPoints = 512;
        // create data series array
        AForge.Math.Complex[] data = new AForge.Math.Complex[numberOfPoints];
        double[,] testValues = new double[numberOfPoints, 2];

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (buttonStart.Text == "Start")
            {
                if (usrp==null)
                    usrp = new multi_usrp();
                
                if (!usrp.isConnected)
                {
                    Console.WriteLine("!-- Cannot connect to USRP device. Check you cable connection.");
                    usrp = null;
                    return;
                }

                if (usrp.IsRXRunning())
                    return;
                
                Console.WriteLine("Using Device: " + usrp.get_pp_string());
                double rate = Math.Pow(2, comboBoxRate.SelectedIndex - 2) * 1e6;
                usrp.set_rx_rate(rate);
                Console.WriteLine("RX rate is " + (usrp.get_rx_rate() / 1e6).ToString() + " MHZ");

                double freq_val;
                if (double.TryParse(textBoxFreq.Text, out freq_val))
                    usrp.set_rx_freq(freq_val * 1e6);
                Console.WriteLine("RX freq. is " + (usrp.get_rx_freq() / 1e6).ToString() + " MHZ");

                usrp.set_rx_gain(trackBarGain.Value);
                Console.WriteLine("RX gain is " + usrp.get_rx_gain().ToString() + " dB");

                // Populating comboBoxAntenna
                string[] anntenas = usrp.get_rx_anntenas();
                for (int i = 0; i < anntenas.Length; i++)
                    comboBoxAntenna.Items.Add(anntenas[i]);
                comboBoxAntenna.SelectedIndex = 0;

                usrp.DataReceiverEvent += OnDataReceiverEvent;

                Console.WriteLine("### Starting ### ");
                usrp.begin_rx_stream();
                buttonStart.Text="Stop";
            }
            else
            {
                usrp.stop_rx_stream();
                buttonStart.Text = "Start";
            }

        }

        private void OnDataReceiverEvent(int[] real, int[] imaginary, int length, rx_metadata_t md)
        {
            if (length < numberOfPoints) // Insufficient data for FFT
                return;
            for (int i = 0; i < numberOfPoints; i++)
                data[i] = new AForge.Math.Complex(real[i], imaginary[i]);
            
            FourierTransform.FFT(data, FourierTransform.Direction.Forward);
            int count = 0;
            for (int i = numberOfPoints/2; i < numberOfPoints; i++)
                testValues[i, 1] = data[count++].Magnitude;

            for (int i = 0; i < numberOfPoints/2; i++)
                testValues[i, 1] = data[count++].Magnitude;

            chart.UpdateDataSeries("Test", testValues);
            //chart.RangeY = new AForge.Range(0, 2048);

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (usrp != null)
                usrp.stop_rx_stream();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Chart:
            // Fill data series
            for (int i = 0; i < numberOfPoints; i++)
            {
                testValues[i, 0] = numberOfPoints-i;
                testValues[i, 1] = 0;
            }
            // add new data series to the chart
            chart.AddDataSeries("Test", Color.DarkGreen, Chart.SeriesType.Line/*.ConnectedDots*/, 1, false);
            // set X range to display
            chart.RangeX = new AForge.Range(0, numberOfPoints);
            chart.RangeY = new AForge.Range(0, 2048);

            // Populating comboBoxRate
            for (int count = -2; count < 6; count++)
                comboBoxRate.Items.Add(Math.Pow(2, count).ToString() + " MHz");
            comboBoxRate.SelectedIndex = 0;

        }

        private void comboBoxRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (usrp == null)
                return;

            double rate = Math.Pow(2, comboBoxRate.SelectedIndex - 2) * 1e6;
            usrp.set_rx_rate(rate);
            Console.WriteLine("RX rate is " + (usrp.get_rx_rate() / 1e6).ToString() + " MHZ");
        }

        private void trackBarGain_Scroll(object sender, EventArgs e)
        {
            if (usrp == null)
                return;

            usrp.set_rx_gain(trackBarGain.Value);
            labelGain.Text = usrp.get_rx_gain().ToString();
        }

        private void buttonFreqSet_Click(object sender, EventArgs e)
        {
            if (usrp == null)
                return;

            double val;
            if (double.TryParse(textBoxFreq.Text, out val))
                usrp.set_rx_freq(val * 1e6);
            
        }

        private void comboBoxAntenna_SelectedIndexChanged(object sender, EventArgs e)
        {
            usrp.set_rx_antenna((string)comboBoxAntenna.SelectedItem);
        }

     }
}
