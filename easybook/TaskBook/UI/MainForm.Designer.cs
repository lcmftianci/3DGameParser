namespace TaskBook.UI
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsmiNewTask = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiTaskList = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiOptions = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiExit = new System.Windows.Forms.ToolStripMenuItem();
            this.tmrDetectRemind = new System.Windows.Forms.Timer(this.components);
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.ContextMenuStrip = this.contextMenuStrip1;
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "notifyIcon1";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon1_MouseClick);
            this.notifyIcon1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon1_MouseDoubleClick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiNewTask,
            this.tsmiTaskList,
            this.toolStripSeparator2,
            this.tsmiOptions,
            this.toolStripSeparator1,
            this.tsmiExit});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(158, 104);
            // 
            // tsmiNewTask
            // 
            this.tsmiNewTask.Image = global::TaskBook.Properties.Resources.NewTask;
            this.tsmiNewTask.Name = "tsmiNewTask";
            this.tsmiNewTask.Size = new System.Drawing.Size(157, 22);
            this.tsmiNewTask.Text = "新建任务";
            this.tsmiNewTask.Click += new System.EventHandler(this.tsmiNewTask_Click);
            // 
            // tsmiTaskList
            // 
            this.tsmiTaskList.Name = "tsmiTaskList";
            this.tsmiTaskList.Size = new System.Drawing.Size(157, 22);
            this.tsmiTaskList.Text = "打开全部任务...";
            this.tsmiTaskList.Click += new System.EventHandler(this.tsmiTaskList_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(154, 6);
            // 
            // tsmiOptions
            // 
            this.tsmiOptions.Name = "tsmiOptions";
            this.tsmiOptions.Size = new System.Drawing.Size(157, 22);
            this.tsmiOptions.Text = "选项...";
            this.tsmiOptions.Click += new System.EventHandler(this.tsmiOptions_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(154, 6);
            // 
            // tsmiExit
            // 
            this.tsmiExit.Name = "tsmiExit";
            this.tsmiExit.Size = new System.Drawing.Size(157, 22);
            this.tsmiExit.Text = "退出";
            this.tsmiExit.Click += new System.EventHandler(this.tsmiExit_Click);
            // 
            // tmrDetectRemind
            // 
            this.tmrDetectRemind.Interval = 600;
            this.tmrDetectRemind.Tick += new System.EventHandler(this.tmrDetectRemind_Tick);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(312, 31);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainForm";
            this.ShowInTaskbar = false;
            this.Text = "Task Book";
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem tsmiNewTask;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem tsmiTaskList;
        private System.Windows.Forms.ToolStripMenuItem tsmiExit;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem tsmiOptions;
        private System.Windows.Forms.Timer tmrDetectRemind;
    }
}