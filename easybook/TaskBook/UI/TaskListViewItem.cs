using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TaskBook.UI
{
    internal class TaskListViewItem : ListViewItem
    {
        public TaskListViewItem(Task task)
        {
            Task = task;
        }

        private Task _task;

        public Task Task
        {
            get { return _task; }
            set
            {
                if (value == null)
                    throw new ArgumentNullException("Task");

                if (_task != value)
                {

                    if (_task != null)
                    _task.PropertyChanged -= new System.ComponentModel.PropertyChangedEventHandler(TaskPropertyChanged);

                    _task = value;

                    _task.PropertyChanged += new System.ComponentModel.PropertyChangedEventHandler(TaskPropertyChanged);

                    Name = value.Id.ToString("N");

                    Update();
                }
            }
        }

        internal static ListViewItem FindItem(ListView lv, Task task)
        {
            string key = task.Id.ToString("N");
            return lv.Items[key];
        }

        private void Update()
        {
            this.Text = _task.Contents;

            if (this.SubItems.Count == 1)
            {
                this.SubItems.AddRange(new string[] { "", "", "" });
            }
            this.SubItems[1].Text = _task.Category;
            this.SubItems[2].Text = string.Format("{0:g}", _task.RemindingTime);
            this.SubItems[3].Text = string.Format("{0:g}", _task.FinishTime);

            this.StateImageIndex = (int)_task.Importance;
        }

        void TaskPropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            Update();
        }


        public override void Remove()
        {
            base.Remove();

            if (_task != null)
                _task.PropertyChanged -= new System.ComponentModel.PropertyChangedEventHandler(TaskPropertyChanged);

        }


    }
}
