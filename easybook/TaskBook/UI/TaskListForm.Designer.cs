namespace TaskBook.UI
{
    partial class TaskListForm
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
            System.Windows.Forms.ColumnHeader columnHeader1;
            System.Windows.Forms.ColumnHeader columnHeader2;
            System.Windows.Forms.ColumnHeader columnHeader3;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TaskListForm));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbNewTask = new System.Windows.Forms.ToolStripButton();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.lvTasks = new System.Windows.Forms.ListView();
            this.ilImportance = new System.Windows.Forms.ImageList(this.components);
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // columnHeader1
            // 
            columnHeader1.Text = "内容";
            columnHeader1.Width = 266;
            // 
            // columnHeader2
            // 
            columnHeader2.Text = "类别";
            columnHeader2.Width = 80;
            // 
            // columnHeader3
            // 
            columnHeader3.Text = "提醒时间";
            columnHeader3.Width = 101;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbNewTask});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(569, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // tsbNewTask
            // 
            this.tsbNewTask.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbNewTask.Image = ((System.Drawing.Image)(resources.GetObject("tsbNewTask.Image")));
            this.tsbNewTask.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbNewTask.Name = "tsbNewTask";
            this.tsbNewTask.Size = new System.Drawing.Size(23, 22);
            this.tsbNewTask.Text = "New Task";
            this.tsbNewTask.Click += new System.EventHandler(this.tsbNewTask_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 499);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(569, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // lvTasks
            // 
            this.lvTasks.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            columnHeader1,
            columnHeader2,
            columnHeader3,
            this.columnHeader4});
            this.lvTasks.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lvTasks.FullRowSelect = true;
            this.lvTasks.Location = new System.Drawing.Point(0, 25);
            this.lvTasks.Name = "lvTasks";
            this.lvTasks.Size = new System.Drawing.Size(569, 474);
            this.lvTasks.StateImageList = this.ilImportance;
            this.lvTasks.TabIndex = 2;
            this.lvTasks.UseCompatibleStateImageBehavior = false;
            this.lvTasks.View = System.Windows.Forms.View.Details;
            this.lvTasks.ItemActivate += new System.EventHandler(this.lvTasks_ItemActivate);
            // 
            // ilImportance
            // 
            this.ilImportance.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("ilImportance.ImageStream")));
            this.ilImportance.TransparentColor = System.Drawing.Color.Transparent;
            this.ilImportance.Images.SetKeyName(0, "importance_memo.gif");
            this.ilImportance.Images.SetKeyName(1, "Flag_greenHS.png");
            this.ilImportance.Images.SetKeyName(2, "Flag_blueHS.png");
            this.ilImportance.Images.SetKeyName(3, "Flag_redHS.png");
            // 
            // columnHeader4
            // 
            this.columnHeader4.Text = "完成时间";
            this.columnHeader4.Width = 89;
            // 
            // TaskListForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(569, 521);
            this.Controls.Add(this.lvTasks);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "TaskListForm";
            this.Text = "MainForm";
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ListView lvTasks;
        private System.Windows.Forms.ToolStripButton tsbNewTask;
        private System.Windows.Forms.ImageList ilImportance;
        private System.Windows.Forms.ColumnHeader columnHeader4;
    }
}