namespace WrapperDemo
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.buttonStart = new System.Windows.Forms.Button();
            this.chart = new AForge.Controls.Chart();
            this.comboBoxRate = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBoxAntenna = new System.Windows.Forms.ComboBox();
            this.buttonFreqSet = new System.Windows.Forms.Button();
            this.trackBarGain = new System.Windows.Forms.TrackBar();
            this.textBoxFreq = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.labelGain = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarGain)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonStart
            // 
            this.buttonStart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonStart.Location = new System.Drawing.Point(431, 397);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(75, 23);
            this.buttonStart.TabIndex = 0;
            this.buttonStart.Text = "Start";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // chart
            // 
            this.chart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chart.Location = new System.Drawing.Point(12, 12);
            this.chart.Name = "chart";
            this.chart.RangeX = ((AForge.Range)(resources.GetObject("chart.RangeX")));
            this.chart.RangeY = ((AForge.Range)(resources.GetObject("chart.RangeY")));
            this.chart.Size = new System.Drawing.Size(494, 229);
            this.chart.TabIndex = 1;
            this.chart.Text = "chart";
            // 
            // comboBoxRate
            // 
            this.comboBoxRate.FormattingEnabled = true;
            this.comboBoxRate.Location = new System.Drawing.Point(84, 20);
            this.comboBoxRate.Name = "comboBoxRate";
            this.comboBoxRate.Size = new System.Drawing.Size(102, 21);
            this.comboBoxRate.TabIndex = 3;
            this.comboBoxRate.SelectedIndexChanged += new System.EventHandler(this.comboBoxRate_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.comboBoxAntenna);
            this.groupBox1.Controls.Add(this.buttonFreqSet);
            this.groupBox1.Controls.Add(this.trackBarGain);
            this.groupBox1.Controls.Add(this.textBoxFreq);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.labelGain);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.comboBoxRate);
            this.groupBox1.Location = new System.Drawing.Point(12, 247);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(494, 144);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 119);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 13);
            this.label5.TabIndex = 11;
            this.label5.Text = "Antenna";
            // 
            // comboBoxAntenna
            // 
            this.comboBoxAntenna.FormattingEnabled = true;
            this.comboBoxAntenna.Location = new System.Drawing.Point(84, 117);
            this.comboBoxAntenna.Name = "comboBoxAntenna";
            this.comboBoxAntenna.Size = new System.Drawing.Size(102, 21);
            this.comboBoxAntenna.TabIndex = 10;
            this.comboBoxAntenna.SelectedIndexChanged += new System.EventHandler(this.comboBoxAntenna_SelectedIndexChanged);
            // 
            // buttonFreqSet
            // 
            this.buttonFreqSet.Location = new System.Drawing.Point(192, 44);
            this.buttonFreqSet.Name = "buttonFreqSet";
            this.buttonFreqSet.Size = new System.Drawing.Size(37, 23);
            this.buttonFreqSet.TabIndex = 9;
            this.buttonFreqSet.Text = "Set";
            this.buttonFreqSet.UseVisualStyleBackColor = true;
            this.buttonFreqSet.Click += new System.EventHandler(this.buttonFreqSet_Click);
            // 
            // trackBarGain
            // 
            this.trackBarGain.LargeChange = 10;
            this.trackBarGain.Location = new System.Drawing.Point(84, 74);
            this.trackBarGain.Maximum = 80;
            this.trackBarGain.Name = "trackBarGain";
            this.trackBarGain.Size = new System.Drawing.Size(102, 45);
            this.trackBarGain.SmallChange = 5;
            this.trackBarGain.TabIndex = 8;
            this.trackBarGain.TickFrequency = 10;
            this.trackBarGain.Scroll += new System.EventHandler(this.trackBarGain_Scroll);
            // 
            // textBoxFreq
            // 
            this.textBoxFreq.Location = new System.Drawing.Point(84, 47);
            this.textBoxFreq.Name = "textBoxFreq";
            this.textBoxFreq.Size = new System.Drawing.Size(102, 20);
            this.textBoxFreq.TabIndex = 7;
            this.textBoxFreq.Text = "100";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(235, 50);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "MHz";
            // 
            // labelGain
            // 
            this.labelGain.AutoSize = true;
            this.labelGain.Location = new System.Drawing.Point(192, 79);
            this.labelGain.Name = "labelGain";
            this.labelGain.Size = new System.Drawing.Size(29, 13);
            this.labelGain.TabIndex = 6;
            this.labelGain.Text = "0 dB";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 79);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Gain";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "RX frequency";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Sample rate";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(518, 432);
            this.Controls.Add(this.chart);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "UHD Wrapper Demo";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarGain)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonStart;
        private AForge.Controls.Chart chart;
        private System.Windows.Forms.ComboBox comboBoxRate;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TrackBar trackBarGain;
        private System.Windows.Forms.TextBox textBoxFreq;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelGain;
        private System.Windows.Forms.Button buttonFreqSet;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBoxAntenna;
    }
}

