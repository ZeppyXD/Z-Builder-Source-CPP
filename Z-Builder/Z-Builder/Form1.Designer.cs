namespace Z_Builder
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
            this.Button1 = new MetroFramework.Controls.MetroButton();
            this.SuspendLayout();
            // 
            // Button1
            // 
            this.Button1.FontSize = MetroFramework.MetroButtonSize.Tall;
            this.Button1.Location = new System.Drawing.Point(46, 76);
            this.Button1.Name = "Button1";
            this.Button1.Size = new System.Drawing.Size(125, 32);
            this.Button1.Style = MetroFramework.MetroColorStyle.Blue;
            this.Button1.TabIndex = 4;
            this.Button1.Text = "Login";
            this.Button1.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.Button1.UseSelectable = true;
            this.Button1.UseStyleColors = true;
            this.Button1.Click += new System.EventHandler(this.metroButton1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BorderStyle = MetroFramework.Forms.MetroFormBorderStyle.FixedSingle;
            this.ClientSize = new System.Drawing.Size(223, 131);
            this.Controls.Add(this.Button1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Resizable = false;
            this.Text = "Z-Builder Login";
            this.TextAlign = MetroFramework.Forms.MetroFormTextAlign.Center;
            this.Theme = MetroFramework.MetroThemeStyle.Dark;
            this.ResumeLayout(false);

        }

        #endregion
        private MetroFramework.Controls.MetroButton Button1;
    }
}

