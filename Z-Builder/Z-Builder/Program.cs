using System;
using System.Configuration;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Z_Builder
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
        static public bool setSetting(string Key, string Value)
        {
            Configuration ConfigFile =
                ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            bool KeyExists = false;

            foreach (string strKey in ConfigFile.AppSettings.Settings.AllKeys)
            {
                if (strKey == Key)
                {
                    KeyExists = true;
                    ConfigFile.AppSettings.Settings[Key].Value = Value;
                    break;
                }
            }
            if (!KeyExists)
            {
                ConfigFile.AppSettings.Settings.Add(Key, Value);
            }
            ConfigFile.Save(ConfigurationSaveMode.Modified);
            ConfigurationManager.RefreshSection("appSettings");
            return true;
        }
    }
}
