namespace TaskBook.UI
{
    partial class OptionsForm
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.nudOpacity = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.chkAutoExpand = new System.Windows.Forms.CheckBox();
            this.chkAutoCollapse = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.nudHeight = new System.Windows.Forms.NumericUpDown();
            this.nudWidth = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.resetThemes = new System.Windows.Forms.Button();
            this.gbColors = new System.Windows.Forms.GroupBox();
            this.lbCaptionColor = new System.Windows.Forms.Label();
            this.lbBackColor = new System.Windows.Forms.Label();
            this.apply = new System.Windows.Forms.Button();
            this.ok = new System.Windows.Forms.Button();
            this.cancel = new System.Windows.Forms.Button();
            this.hktbAddNew = new TaskBook.UI.HotKeyTextBox();
            this.hktbShowAll = new TaskBook.UI.HotKeyTextBox();
            this.bnFont = new TaskBook.UI.FontButton();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudOpacity)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudWidth)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.gbColors.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(374, 343);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox3);
            this.tabPage1.Controls.Add(this.groupBox2);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(366, 317);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "常规";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.hktbAddNew);
            this.groupBox3.Controls.Add(this.hktbShowAll);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(4, 221);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(356, 100);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "热键设置";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(17, 29);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "全部显示：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 1;
            this.label4.Text = "新便签：";
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.nudOpacity);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.chkAutoExpand);
            this.groupBox2.Controls.Add(this.chkAutoCollapse);
            this.groupBox2.Location = new System.Drawing.Point(6, 114);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(354, 100);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "置顶设置";
            // 
            // nudOpacity
            // 
            this.nudOpacity.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.nudOpacity.Location = new System.Drawing.Point(289, 15);
            this.nudOpacity.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nudOpacity.Name = "nudOpacity";
            this.nudOpacity.Size = new System.Drawing.Size(46, 21);
            this.nudOpacity.TabIndex = 3;
            this.nudOpacity.Value = new decimal(new int[] {
            80,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(188, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "收缩后透明度(%)";
            // 
            // chkAutoExpand
            // 
            this.chkAutoExpand.AutoSize = true;
            this.chkAutoExpand.Location = new System.Drawing.Point(17, 43);
            this.chkAutoExpand.Name = "chkAutoExpand";
            this.chkAutoExpand.Size = new System.Drawing.Size(132, 16);
            this.chkAutoExpand.TabIndex = 1;
            this.chkAutoExpand.Text = "获得焦点后自动展开";
            this.chkAutoExpand.UseVisualStyleBackColor = true;
            // 
            // chkAutoCollapse
            // 
            this.chkAutoCollapse.AutoSize = true;
            this.chkAutoCollapse.Location = new System.Drawing.Point(17, 20);
            this.chkAutoCollapse.Name = "chkAutoCollapse";
            this.chkAutoCollapse.Size = new System.Drawing.Size(132, 16);
            this.chkAutoCollapse.TabIndex = 0;
            this.chkAutoCollapse.Text = "失去焦点后自动收缩";
            this.chkAutoCollapse.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.nudHeight);
            this.groupBox1.Controls.Add(this.nudWidth);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.bnFont);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(6, 15);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(354, 93);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "便签设置";
            // 
            // nudHeight
            // 
            this.nudHeight.Location = new System.Drawing.Point(177, 58);
            this.nudHeight.Maximum = new decimal(new int[] {
            400,
            0,
            0,
            0});
            this.nudHeight.Minimum = new decimal(new int[] {
            80,
            0,
            0,
            0});
            this.nudHeight.Name = "nudHeight";
            this.nudHeight.Size = new System.Drawing.Size(67, 21);
            this.nudHeight.TabIndex = 3;
            this.nudHeight.Value = new decimal(new int[] {
            80,
            0,
            0,
            0});
            // 
            // nudWidth
            // 
            this.nudWidth.Location = new System.Drawing.Point(94, 58);
            this.nudWidth.Maximum = new decimal(new int[] {
            400,
            0,
            0,
            0});
            this.nudWidth.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.nudWidth.Name = "nudWidth";
            this.nudWidth.Size = new System.Drawing.Size(67, 21);
            this.nudWidth.TabIndex = 3;
            this.nudWidth.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 60);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "新便签尺寸";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "默认字体";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.resetThemes);
            this.tabPage2.Controls.Add(this.gbColors);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(366, 317);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "外观";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // resetThemes
            // 
            this.resetThemes.Location = new System.Drawing.Point(6, 187);
            this.resetThemes.Name = "resetThemes";
            this.resetThemes.Size = new System.Drawing.Size(75, 23);
            this.resetThemes.TabIndex = 1;
            this.resetThemes.Text = "默认值";
            this.resetThemes.UseVisualStyleBackColor = true;
            this.resetThemes.Click += new System.EventHandler(this.resetThemes_Click);
            // 
            // gbColors
            // 
            this.gbColors.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gbColors.Controls.Add(this.lbCaptionColor);
            this.gbColors.Controls.Add(this.lbBackColor);
            this.gbColors.Location = new System.Drawing.Point(6, 6);
            this.gbColors.Name = "gbColors";
            this.gbColors.Size = new System.Drawing.Size(354, 175);
            this.gbColors.TabIndex = 0;
            this.gbColors.TabStop = false;
            this.gbColors.Text = "色彩";
            // 
            // lbCaptionColor
            // 
            this.lbCaptionColor.AutoSize = true;
            this.lbCaptionColor.Location = new System.Drawing.Point(236, 21);
            this.lbCaptionColor.Name = "lbCaptionColor";
            this.lbCaptionColor.Size = new System.Drawing.Size(65, 12);
            this.lbCaptionColor.TabIndex = 1;
            this.lbCaptionColor.Text = "标题背景色";
            // 
            // lbBackColor
            // 
            this.lbBackColor.AutoSize = true;
            this.lbBackColor.Location = new System.Drawing.Point(136, 21);
            this.lbBackColor.Name = "lbBackColor";
            this.lbBackColor.Size = new System.Drawing.Size(41, 12);
            this.lbBackColor.TabIndex = 0;
            this.lbBackColor.Text = "背景色";
            // 
            // apply
            // 
            this.apply.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.apply.Location = new System.Drawing.Point(147, 369);
            this.apply.Name = "apply";
            this.apply.Size = new System.Drawing.Size(75, 23);
            this.apply.TabIndex = 1;
            this.apply.Text = "应用";
            this.apply.UseVisualStyleBackColor = true;
            this.apply.Click += new System.EventHandler(this.apply_Click);
            // 
            // ok
            // 
            this.ok.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ok.Location = new System.Drawing.Point(229, 369);
            this.ok.Name = "ok";
            this.ok.Size = new System.Drawing.Size(75, 23);
            this.ok.TabIndex = 2;
            this.ok.Text = "确定";
            this.ok.UseVisualStyleBackColor = true;
            this.ok.Click += new System.EventHandler(this.ok_Click);
            // 
            // cancel
            // 
            this.cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancel.Location = new System.Drawing.Point(311, 368);
            this.cancel.Name = "cancel";
            this.cancel.Size = new System.Drawing.Size(75, 23);
            this.cancel.TabIndex = 3;
            this.cancel.Text = "取消";
            this.cancel.UseVisualStyleBackColor = true;
            this.cancel.Click += new System.EventHandler(this.cancel_Click);
            // 
            // hktbAddNew
            // 
            this.hktbAddNew.BackColor = System.Drawing.SystemColors.Window;
            this.hktbAddNew.Location = new System.Drawing.Point(96, 53);
            this.hktbAddNew.Name = "hktbAddNew";
            this.hktbAddNew.ReadOnly = true;
            this.hktbAddNew.Size = new System.Drawing.Size(150, 21);
            this.hktbAddNew.TabIndex = 2;
            // 
            // hktbShowAll
            // 
            this.hktbShowAll.BackColor = System.Drawing.SystemColors.Window;
            this.hktbShowAll.Location = new System.Drawing.Point(96, 20);
            this.hktbShowAll.Name = "hktbShowAll";
            this.hktbShowAll.ReadOnly = true;
            this.hktbShowAll.Size = new System.Drawing.Size(150, 21);
            this.hktbShowAll.TabIndex = 2;
            // 
            // bnFont
            // 
            this.bnFont.Location = new System.Drawing.Point(94, 16);
            this.bnFont.Name = "bnFont";
            this.bnFont.Size = new System.Drawing.Size(241, 32);
            this.bnFont.TabIndex = 1;
            this.bnFont.Text = "fontButton1";
            this.bnFont.UseVisualStyleBackColor = true;
            // 
            // OptionsForm
            // 
            this.AcceptButton = this.ok;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancel;
            this.ClientSize = new System.Drawing.Size(398, 403);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.ok);
            this.Controls.Add(this.apply);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "OptionsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "选项";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudOpacity)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudWidth)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.gbColors.ResumeLayout(false);
            this.gbColors.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.NumericUpDown nudOpacity;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chkAutoExpand;
        private System.Windows.Forms.CheckBox chkAutoCollapse;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox gbColors;
        private System.Windows.Forms.Button apply;
        private System.Windows.Forms.Button ok;
        private System.Windows.Forms.Button cancel;
        private System.Windows.Forms.Label lbCaptionColor;
        private System.Windows.Forms.Label lbBackColor;
        private FontButton bnFont;
        private System.Windows.Forms.NumericUpDown nudHeight;
        private System.Windows.Forms.NumericUpDown nudWidth;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button resetThemes;
        private HotKeyTextBox hktbAddNew;
        private HotKeyTextBox hktbShowAll;
    }
}