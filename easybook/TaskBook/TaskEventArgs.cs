using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TaskBook
{
    public class TaskEventArgs : EventArgs
    {
        public TaskEventArgs(Task task)
        {
            _task = task;
        }

        private Task _task;

        public Task Task
        {
            get { return _task; }
        }

    }
}
