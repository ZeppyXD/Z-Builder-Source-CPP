using System;
using System.Diagnostics;
using System.IO;

namespace RecoverSaveDats
{
    class Program
    {
        static void Main(string[] args)
        {
            RecoverSaveDats();
        }
        static void RecoverSaveDats()
        {
            try
            {
                string tempPath = Path.GetTempPath();
                string ZBRecoveredFolder = tempPath + "\\ZBRecoveredFolder";
                string ps1file = ZBRecoveredFolder + "\\RecoverFiles.ps1";
                try { File.Delete(ps1file); } catch { };
                using (var tw = new StreamWriter(ps1file, true))
                {
                    tw.WriteLine(string.Join(Environment.NewLine, "$shell = New-Object -ComObject Shell.Application", "$recycleBin = $shell.Namespace(0xA) #Recycle Bin", "$recycleBin.Items() | %{Copy-Item $_.Path (\"" + ZBRecoveredFolder + "\\{0}\\" + " -f ($_.Name+[string](Get-Random)))}"));
                }
                var StartInfo = new ProcessStartInfo();
                StartInfo.FileName = "powershell.exe";
                StartInfo.Arguments = "-NoProfile -ExecutionPolicy unrestricted -file \"" + ps1file + "\"";
                StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                using (Process RecycleBinGrabber = Process.Start(StartInfo))
                {
                    RecycleBinGrabber.WaitForExit();
                }
            }
            catch { }
        }
    }
}
