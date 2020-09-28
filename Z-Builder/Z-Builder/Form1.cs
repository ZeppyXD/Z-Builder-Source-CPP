using System;
using System.Configuration;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Z_Builder
{
    public partial class Form1 : MetroFramework.Forms.MetroForm
    {
        public Form1()
        {
            InitializeComponent();
            TextBox1.Text = ConfigurationManager.AppSettings["ID"];
            TextBox2.Text = ConfigurationManager.AppSettings["password"];
            metroTextBox1.Text = ConfigurationManager.AppSettings["LicenseKey"];
        }

        private void metroButton1_Click(object sender, EventArgs e)
        {
            try
            {
                string HWID = String.Empty;
                ManagementObjectSearcher moSearcher = new ManagementObjectSearcher("root\\CIMV2", "SELECT * FROM Win32_Processor");
                foreach (ManagementObject mngObj in moSearcher.Get())
                {
                    HWID = mngObj["ProcessorId"].ToString();
                }
                string RawInfo = new System.Net.WebClient() { Proxy = null }.DownloadString("https://pastebin.com/raw/3beYQ33f");
                String[] Info = RawInfo.Split(new[] { '\n', '\r', ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                string key = TextBox1.Text + "/" + TextBox2.Text + "/" + HWID + "/" + metroTextBox1.Text;
                Program.setSetting("ID", TextBox1.Text);
                Program.setSetting("password", TextBox2.Text);
                Program.setSetting("LicenseKey", metroTextBox1.Text);
                if (Info.Contains(key))
                {
                    MessageBox.Show("Sucessfully logged in!");
                    this.Hide();
                    var form2 = new Form2(TextBox1.Text, metroTextBox1.Text);
                    form2.Closed += (s, args) => this.Close();
                    form2.Show();
                }
                else
                {
                    MessageBox.Show("Invalid account!");
                }
            }
            catch
            {
                MessageBox.Show("Internet connection is required.");
            }
        }
    }
}
