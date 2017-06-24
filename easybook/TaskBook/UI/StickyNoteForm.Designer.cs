namespace TaskBook.UI
{
    partial class StickyNoteForm
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.ToolStripMenuItem 停止提醒ToolStripMenuItem;
            System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
            System.Windows.Forms.ToolStripMenuItem 推迟5分钟ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 推迟10分钟ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 推迟20分钟ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 推迟1小时ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 推迟4小时ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 推迟1天ToolStripMenuItem;
            System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
            System.Windows.Forms.ToolStripMenuItem 分钟以后ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 分钟以后ToolStripMenuItem1;
            System.Windows.Forms.ToolStripMenuItem 分钟以后ToolStripMenuItem2;
            System.Windows.Forms.ToolStripMenuItem 小时以后ToolStripMenuItem;
            System.Windows.Forms.ToolStripMenuItem 小时以后ToolStripMenuItem1;
            System.Windows.Forms.ToolStripMenuItem 小时以后ToolStripMenuItem2;
            System.Windows.Forms.ToolStripMenuItem 指定时间ToolStripMenuItem;
            System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiCut = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiPastePlain = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiFont = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiClose = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiFinishAndClose = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiDeleteTask = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiQuit = new System.Windows.Forms.ToolStripMenuItem();
            this.pnTitle = new System.Windows.Forms.Panel();
            this.mnuStopRemind = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.mnuSetRemindTime = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsmiClearReminding = new System.Windows.Forms.ToolStripMenuItem();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.tbFinish = new TaskBook.UI.ToolButton();
            this.tbRemind = new TaskBook.UI.ToolButton();
            this.tbPin = new TaskBook.UI.ToolButton();
            this.tbNew = new TaskBook.UI.ToolButton();
            this.tmrRemind = new TaskBook.UI.RemindTimer();
            停止提醒ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            推迟5分钟ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            推迟10分钟ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            推迟20分钟ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            推迟1小时ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            推迟4小时ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            推迟1天ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            分钟以后ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            分钟以后ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            分钟以后ToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            小时以后ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            小时以后ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            小时以后ToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            指定时间ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.contextMenuStrip1.SuspendLayout();
            this.pnTitle.SuspendLayout();
            this.mnuStopRemind.SuspendLayout();
            this.mnuSetRemindTime.SuspendLayout();
            this.SuspendLayout();
            // 
            // 停止提醒ToolStripMenuItem
            // 
            停止提醒ToolStripMenuItem.Name = "停止提醒ToolStripMenuItem";
            停止提醒ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            停止提醒ToolStripMenuItem.Text = "停止提醒";
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new System.Drawing.Size(135, 6);
            // 
            // 推迟5分钟ToolStripMenuItem
            // 
            推迟5分钟ToolStripMenuItem.Name = "推迟5分钟ToolStripMenuItem";
            推迟5分钟ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            推迟5分钟ToolStripMenuItem.Tag = "0:5:0";
            推迟5分钟ToolStripMenuItem.Text = "推迟5分钟";
            // 
            // 推迟10分钟ToolStripMenuItem
            // 
            推迟10分钟ToolStripMenuItem.Name = "推迟10分钟ToolStripMenuItem";
            推迟10分钟ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            推迟10分钟ToolStripMenuItem.Tag = "0:10:0";
            推迟10分钟ToolStripMenuItem.Text = "推迟10分钟";
            // 
            // 推迟20分钟ToolStripMenuItem
            // 
            推迟20分钟ToolStripMenuItem.Name = "推迟20分钟ToolStripMenuItem";
            推迟20分钟ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            推迟20分钟ToolStripMenuItem.Tag = "0:20:0";
            推迟20分钟ToolStripMenuItem.Text = "推迟20分钟";
            // 
            // 推迟1小时ToolStripMenuItem
            // 
            推迟1小时ToolStripMenuItem.Name = "推迟1小时ToolStripMenuItem";
            推迟1小时ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            推迟1小时ToolStripMenuItem.Tag = "1:0:0";
            推迟1小时ToolStripMenuItem.Text = "推迟1小时";
            // 
            // 推迟4小时ToolStripMenuItem
            // 
            推迟4小时ToolStripMenuItem.Name = "推迟4小时ToolStripMenuItem";
            推迟4小时ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            推迟4小时ToolStripMenuItem.Tag = "4:0:0";
            推迟4小时ToolStripMenuItem.Text = "推迟4小时";
            // 
            // 推迟1天ToolStripMenuItem
            // 
            推迟1天ToolStripMenuItem.Name = "推迟1天ToolStripMenuItem";
            推迟1天ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            推迟1天ToolStripMenuItem.Tag = "1 0:0:0";
            推迟1天ToolStripMenuItem.Text = "推迟1天";
            // 
            // toolStripSeparator5
            // 
            toolStripSeparator5.Name = "toolStripSeparator5";
            toolStripSeparator5.Size = new System.Drawing.Size(135, 6);
            // 
            // 分钟以后ToolStripMenuItem
            // 
            分钟以后ToolStripMenuItem.Name = "分钟以后ToolStripMenuItem";
            分钟以后ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            分钟以后ToolStripMenuItem.Tag = "0:10:0";
            分钟以后ToolStripMenuItem.Text = "10分钟以后";
            // 
            // 分钟以后ToolStripMenuItem1
            // 
            分钟以后ToolStripMenuItem1.Name = "分钟以后ToolStripMenuItem1";
            分钟以后ToolStripMenuItem1.Size = new System.Drawing.Size(138, 22);
            分钟以后ToolStripMenuItem1.Tag = "0:20:0";
            分钟以后ToolStripMenuItem1.Text = "20分钟以后";
            // 
            // 分钟以后ToolStripMenuItem2
            // 
            分钟以后ToolStripMenuItem2.Name = "分钟以后ToolStripMenuItem2";
            分钟以后ToolStripMenuItem2.Size = new System.Drawing.Size(138, 22);
            分钟以后ToolStripMenuItem2.Tag = "0:30:0";
            分钟以后ToolStripMenuItem2.Text = "30分钟以后";
            // 
            // 小时以后ToolStripMenuItem
            // 
            小时以后ToolStripMenuItem.Name = "小时以后ToolStripMenuItem";
            小时以后ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            小时以后ToolStripMenuItem.Tag = "1:0:0";
            小时以后ToolStripMenuItem.Text = "1小时以后";
            // 
            // 小时以后ToolStripMenuItem1
            // 
            小时以后ToolStripMenuItem1.Name = "小时以后ToolStripMenuItem1";
            小时以后ToolStripMenuItem1.Size = new System.Drawing.Size(138, 22);
            小时以后ToolStripMenuItem1.Tag = "2:0:0";
            小时以后ToolStripMenuItem1.Text = "2小时以后";
            // 
            // 小时以后ToolStripMenuItem2
            // 
            小时以后ToolStripMenuItem2.Name = "小时以后ToolStripMenuItem2";
            小时以后ToolStripMenuItem2.Size = new System.Drawing.Size(138, 22);
            小时以后ToolStripMenuItem2.Tag = "4:0:0";
            小时以后ToolStripMenuItem2.Text = "4小时以后";
            // 
            // 指定时间ToolStripMenuItem
            // 
            指定时间ToolStripMenuItem.Name = "指定时间ToolStripMenuItem";
            指定时间ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            指定时间ToolStripMenuItem.Tag = "Custom";
            指定时间ToolStripMenuItem.Text = "指定时间...";
            // 
            // toolStripSeparator6
            // 
            toolStripSeparator6.Name = "toolStripSeparator6";
            toolStripSeparator6.Size = new System.Drawing.Size(135, 6);
            // 
            // richTextBox1
            // 
            this.richTextBox1.AcceptsTab = true;
            this.richTextBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBox1.BackColor = System.Drawing.Color.White;
            this.richTextBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBox1.ContextMenuStrip = this.contextMenuStrip1;
            this.richTextBox1.HideSelection = false;
            this.richTextBox1.Location = new System.Drawing.Point(7, 26);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None;
            this.richTextBox1.Size = new System.Drawing.Size(180, 87);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            this.richTextBox1.SelectionChanged += new System.EventHandler(this.richTextBox1_SelectionChanged);
            this.richTextBox1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.richTextBox1_KeyDown);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripSeparator3,
            this.tsmiCut,
            this.tsmiCopy,
            this.tsmiPaste,
            this.tsmiPastePlain,
            this.tsmiFont,
            this.toolStripSeparator2,
            this.tsmiClose,
            this.tsmiFinishAndClose,
            this.tsmiDeleteTask,
            this.toolStripSeparator4,
            this.tsmiQuit});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(161, 220);
            this.contextMenuStrip1.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStrip1_Opening);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(157, 6);
            // 
            // tsmiCut
            // 
            this.tsmiCut.Image = global::TaskBook.Properties.Resources.CutHS;
            this.tsmiCut.Name = "tsmiCut";
            this.tsmiCut.Size = new System.Drawing.Size(160, 22);
            this.tsmiCut.Tag = "cut";
            this.tsmiCut.Text = "剪切";
            this.tsmiCut.Click += new System.EventHandler(this.ClipboardAction);
            // 
            // tsmiCopy
            // 
            this.tsmiCopy.Image = global::TaskBook.Properties.Resources.CopyHS;
            this.tsmiCopy.Name = "tsmiCopy";
            this.tsmiCopy.Size = new System.Drawing.Size(160, 22);
            this.tsmiCopy.Tag = "copy";
            this.tsmiCopy.Text = "复制";
            this.tsmiCopy.Click += new System.EventHandler(this.ClipboardAction);
            // 
            // tsmiPaste
            // 
            this.tsmiPaste.Image = global::TaskBook.Properties.Resources.PasteHS;
            this.tsmiPaste.Name = "tsmiPaste";
            this.tsmiPaste.Size = new System.Drawing.Size(160, 22);
            this.tsmiPaste.Tag = "paste";
            this.tsmiPaste.Text = "粘贴";
            this.tsmiPaste.Click += new System.EventHandler(this.ClipboardAction);
            // 
            // tsmiPastePlain
            // 
            this.tsmiPastePlain.Name = "tsmiPastePlain";
            this.tsmiPastePlain.Size = new System.Drawing.Size(160, 22);
            this.tsmiPastePlain.Tag = "paste.plain";
            this.tsmiPastePlain.Text = "粘贴为纯文本";
            this.tsmiPastePlain.Click += new System.EventHandler(this.ClipboardAction);
            // 
            // tsmiFont
            // 
            this.tsmiFont.Image = global::TaskBook.Properties.Resources.FontDialogHS;
            this.tsmiFont.Name = "tsmiFont";
            this.tsmiFont.Size = new System.Drawing.Size(160, 22);
            this.tsmiFont.Text = "字体...";
            this.tsmiFont.Click += new System.EventHandler(this.tsmiFont_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(157, 6);
            // 
            // tsmiClose
            // 
            this.tsmiClose.Name = "tsmiClose";
            this.tsmiClose.Size = new System.Drawing.Size(160, 22);
            this.tsmiClose.Text = "关闭此便签";
            this.tsmiClose.Click += new System.EventHandler(this.tsmiClose_Click);
            // 
            // tsmiFinishAndClose
            // 
            this.tsmiFinishAndClose.Image = global::TaskBook.Properties.Resources.finish;
            this.tsmiFinishAndClose.Name = "tsmiFinishAndClose";
            this.tsmiFinishAndClose.Size = new System.Drawing.Size(160, 22);
            this.tsmiFinishAndClose.Text = "完成任务并关闭";
            this.tsmiFinishAndClose.Click += new System.EventHandler(this.tsmiFinishAndClose_Click);
            // 
            // tsmiDeleteTask
            // 
            this.tsmiDeleteTask.Image = global::TaskBook.Properties.Resources.DeleteHS;
            this.tsmiDeleteTask.Name = "tsmiDeleteTask";
            this.tsmiDeleteTask.Size = new System.Drawing.Size(160, 22);
            this.tsmiDeleteTask.Text = "删除任务";
            this.tsmiDeleteTask.Click += new System.EventHandler(this.tsmiDeleteTask_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(157, 6);
            // 
            // tsmiQuit
            // 
            this.tsmiQuit.Name = "tsmiQuit";
            this.tsmiQuit.Size = new System.Drawing.Size(160, 22);
            this.tsmiQuit.Text = "退出";
            this.tsmiQuit.Click += new System.EventHandler(this.tsmiQuit_Click);
            // 
            // pnTitle
            // 
            this.pnTitle.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pnTitle.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.pnTitle.ContextMenuStrip = this.contextMenuStrip1;
            this.pnTitle.Controls.Add(this.tbFinish);
            this.pnTitle.Controls.Add(this.tbRemind);
            this.pnTitle.Controls.Add(this.tbPin);
            this.pnTitle.Controls.Add(this.tbNew);
            this.pnTitle.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.pnTitle.Location = new System.Drawing.Point(1, 1);
            this.pnTitle.Name = "pnTitle";
            this.pnTitle.Size = new System.Drawing.Size(189, 22);
            this.pnTitle.TabIndex = 2;
            this.pnTitle.Paint += new System.Windows.Forms.PaintEventHandler(this.pnTitle_Paint);
            this.pnTitle.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.pnTitle_MouseDoubleClick);
            this.pnTitle.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnTitle_MouseDown);
            this.pnTitle.MouseEnter += new System.EventHandler(this.pnTitle_MouseEnter);
            this.pnTitle.MouseLeave += new System.EventHandler(this.pnTitle_MouseLeave);
            this.pnTitle.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnTitle_MouseMove);
            this.pnTitle.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pnTitle_MouseUp);
            // 
            // mnuStopRemind
            // 
            this.mnuStopRemind.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            停止提醒ToolStripMenuItem,
            toolStripSeparator1,
            推迟5分钟ToolStripMenuItem,
            推迟10分钟ToolStripMenuItem,
            推迟20分钟ToolStripMenuItem,
            推迟1小时ToolStripMenuItem,
            推迟4小时ToolStripMenuItem,
            推迟1天ToolStripMenuItem});
            this.mnuStopRemind.Name = "mnuStopRemind";
            this.mnuStopRemind.Size = new System.Drawing.Size(139, 164);
            this.mnuStopRemind.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.mnuStopRemind_ItemClicked);
            // 
            // mnuSetRemindTime
            // 
            this.mnuSetRemindTime.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiClearReminding,
            toolStripSeparator5,
            分钟以后ToolStripMenuItem,
            分钟以后ToolStripMenuItem1,
            分钟以后ToolStripMenuItem2,
            小时以后ToolStripMenuItem,
            小时以后ToolStripMenuItem1,
            小时以后ToolStripMenuItem2,
            toolStripSeparator6,
            指定时间ToolStripMenuItem});
            this.mnuSetRemindTime.Name = "mnuSetRemindTime";
            this.mnuSetRemindTime.Size = new System.Drawing.Size(139, 192);
            this.mnuSetRemindTime.Opening += new System.ComponentModel.CancelEventHandler(this.mnuSetRemindTime_Opening);
            this.mnuSetRemindTime.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.mnuSetRemindTime_ItemClicked);
            // 
            // tsmiClearReminding
            // 
            this.tsmiClearReminding.Name = "tsmiClearReminding";
            this.tsmiClearReminding.Size = new System.Drawing.Size(138, 22);
            this.tsmiClearReminding.Text = "取消提醒";
            // 
            // tbFinish
            // 
            this.tbFinish.Image = global::TaskBook.Properties.Resources.finish;
            this.tbFinish.ImageSize = new System.Drawing.Size(12, 12);
            this.tbFinish.Location = new System.Drawing.Point(42, 2);
            this.tbFinish.Name = "tbFinish";
            this.tbFinish.Size = new System.Drawing.Size(18, 18);
            this.tbFinish.TabIndex = 5;
            this.tbFinish.TabStop = false;
            this.tbFinish.Text = "toolButton3";
            this.toolTip1.SetToolTip(this.tbFinish, "完成并关闭此便签");
            this.tbFinish.UseVisualStyleBackColor = false;
            this.tbFinish.Click += new System.EventHandler(this.tsmiFinishAndClose_Click);
            // 
            // tbRemind
            // 
            this.tbRemind.Image = global::TaskBook.Properties.Resources.Reminder_gray;
            this.tbRemind.ImageSize = new System.Drawing.Size(12, 12);
            this.tbRemind.Location = new System.Drawing.Point(22, 2);
            this.tbRemind.Name = "tbRemind";
            this.tbRemind.Size = new System.Drawing.Size(18, 18);
            this.tbRemind.TabIndex = 4;
            this.tbRemind.TabStop = false;
            this.tbRemind.Text = "toolButton2";
            this.tbRemind.UseVisualStyleBackColor = false;
            this.tbRemind.Click += new System.EventHandler(this.tbRemind_Click);
            // 
            // tbPin
            // 
            this.tbPin.Image = global::TaskBook.Properties.Resources.pin_gray;
            this.tbPin.ImageSize = new System.Drawing.Size(12, 12);
            this.tbPin.Location = new System.Drawing.Point(2, 2);
            this.tbPin.Name = "tbPin";
            this.tbPin.Size = new System.Drawing.Size(18, 18);
            this.tbPin.TabIndex = 3;
            this.tbPin.TabStop = false;
            this.tbPin.Text = "toolButton1";
            this.tbPin.UseVisualStyleBackColor = false;
            this.tbPin.Click += new System.EventHandler(this.tbPin_Click);
            // 
            // tbNew
            // 
            this.tbNew.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.tbNew.Image = global::TaskBook.Properties.Resources.NewTask;
            this.tbNew.ImageSize = new System.Drawing.Size(12, 12);
            this.tbNew.Location = new System.Drawing.Point(168, 2);
            this.tbNew.Name = "tbNew";
            this.tbNew.Size = new System.Drawing.Size(18, 18);
            this.tbNew.TabIndex = 2;
            this.tbNew.TabStop = false;
            this.tbNew.Text = "toolButton1";
            this.toolTip1.SetToolTip(this.tbNew, "添加新的任务和便签");
            this.tbNew.UseVisualStyleBackColor = false;
            this.tbNew.Click += new System.EventHandler(this.toolButton1_Click);
            // 
            // tmrRemind
            // 
            this.tmrRemind.Interval = 600;
            this.tmrRemind.Tick += new System.EventHandler(this.tmrRemind_Tick);
            // 
            // StickyNoteForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.ClientSize = new System.Drawing.Size(194, 120);
            this.ControlBox = false;
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.pnTitle);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(180, 120);
            this.Name = "StickyNoteForm";
            this.Padding = new System.Windows.Forms.Padding(1);
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.LocationChanged += new System.EventHandler(this.BoundsChanged);
            this.SizeChanged += new System.EventHandler(this.BoundsChanged);
            this.contextMenuStrip1.ResumeLayout(false);
            this.pnTitle.ResumeLayout(false);
            this.mnuStopRemind.ResumeLayout(false);
            this.mnuSetRemindTime.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem tsmiCut;
        private System.Windows.Forms.ToolStripMenuItem tsmiCopy;
        private System.Windows.Forms.ToolStripMenuItem tsmiPaste;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem tsmiFont;
        private System.Windows.Forms.ToolStripMenuItem tsmiPastePlain;
        private System.Windows.Forms.Panel pnTitle;
        private ToolButton tbNew;
        private System.Windows.Forms.ToolStripMenuItem tsmiClose;
        private System.Windows.Forms.ToolStripMenuItem tsmiQuit;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private ToolButton tbRemind;
        private ToolButton tbPin;
        private ToolButton tbFinish;
        private System.Windows.Forms.ToolStripMenuItem tsmiFinishAndClose;
        private System.Windows.Forms.ToolStripMenuItem tsmiDeleteTask;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private RemindTimer tmrRemind;
        private System.Windows.Forms.ContextMenuStrip mnuStopRemind;
        private System.Windows.Forms.ContextMenuStrip mnuSetRemindTime;
        private System.Windows.Forms.ToolStripMenuItem tsmiClearReminding;
        private System.Windows.Forms.ToolTip toolTip1;
    }
}