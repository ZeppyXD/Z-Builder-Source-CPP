using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Management;

namespace HWID_Displayer
{
    static class Program
    {
        static void Main()
        {
            string HWID = String.Empty;
            ManagementObjectSearcher moSearcher = new ManagementObjectSearcher("root\\CIMV2", "SELECT * FROM Win32_Processor");
            foreach (ManagementObject mngObj in moSearcher.Get())
            {
                HWID = mngObj["ProcessorId"].ToString();
            }
            MessageBox.Show(HWID);
        }
    }
}
