using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TaskBook.UI
{
    public partial class TaskListForm : Form
    {
        public TaskListForm()
        {
            InitializeComponent();

            Program.User.TaskDeleted += new EventHandler<TaskEventArgs>(User_TaskDeleted);
            Program.User.TaskAdded += new EventHandler<TaskEventArgs>(User_TaskAdded);
        }

        void User_TaskAdded(object sender, TaskEventArgs e)
        {
            lvTasks.Items.Insert(0, new TaskListViewItem(e.Task));
        }

        void User_TaskDeleted(object sender, TaskEventArgs e)
        {
            ListViewItem item = TaskListViewItem.FindItem(lvTasks, e.Task);
            if (item != null) item.Remove();
        }

        private void LoadTasks()
        {
            Task[] tasks = Program.User.GetTasks();

            lvTasks.BeginUpdate();
            lvTasks.Items.Clear();

            lvTasks.Items.AddRange(tasks.Select(o => new TaskListViewItem(o)).Cast<ListViewItem>().ToArray());

            lvTasks.EndUpdate();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            LoadTasks();
        }

        private void tsbNewTask_Click(object sender, EventArgs e)
        {
        }

        private void lvTasks_ItemActivate(object sender, EventArgs e)
        {
            //Program.MainForm.ShowStickyNote(((TaskListViewItem)lvTasks.FocusedItem).Task, null);
        }

        protected override void OnFormClosed(FormClosedEventArgs e)
        {
            base.OnFormClosed(e);

            Program.User.TaskDeleted -= new EventHandler<TaskEventArgs>(User_TaskDeleted);
            Program.User.TaskAdded -= new EventHandler<TaskEventArgs>(User_TaskAdded);
        }
    }
}
