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
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            _stickyNoteForms = new List<StickyNoteForm>();

            Program.User.TaskDeleted += new EventHandler<TaskEventArgs>(User_TaskDeleted);

        }

        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);
            RegisterHotKeys(Program.User.Options);
        }

        protected override void OnHandleDestroyed(EventArgs e)
        {
            base.OnHandleDestroyed(e);
            UnregisterHotKeys();
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == NativeMethods.WM_HOTKEY)
            {
                int id = m.WParam.ToInt32();

                switch ((HotKeyType)id)
                {
                    case HotKeyType.ShowAllStickyNotes:
                        BringAllStickyNoteFormsToFront();
                        break;
                    case HotKeyType.AddNewStickyNote:
                        NewStickyNote(null);
                        break;
                    default:
                        base.WndProc(ref m);
                        break;
                }
            }
            else
                base.WndProc(ref m);
        }

        Dictionary<HotKeyType, HotKey> _hotKeys = new Dictionary<HotKeyType, HotKey>();

        private void RegisterHotKeys(UserOptions options)
        {
            int failcount = 0;
            
            if (_hotKeys.Count > 0) UnregisterHotKeys();        // 在注册新的热键之前先注销之前注册的热键

            foreach (HotKeyType type in Enum.GetValues(typeof(HotKeyType)))
            {
                HotKey hk = options.GetHotKey(type);
                if (!hk.IsEmpty)
                {
                    if (NativeMethods.RegisterHotKey(this.Handle, (int)type, hk.Modifiers, (int)hk.KeyCode))
                        _hotKeys.Add(type, hk);
                    else
                        failcount++;
                }
            }

            if (failcount > 0)
                MessageBox.Show("一个或多个系统热键注册失败，建议更改热键设置！", ProductName, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void UnregisterHotKeys()
        {
            foreach (var entry in _hotKeys)
                NativeMethods.UnregisterHotKey(this.Handle, (int)entry.Key);
            _hotKeys.Clear();
        }

        void User_TaskDeleted(object sender, TaskEventArgs e)
        {
            Guid id = e.Task.Id;

            var form = _stickyNoteForms.SingleOrDefault(o => o.Task.Id == id);

            if (form != null)
                form.Close();
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            this.Location = new Point(-10, -this.Height);
            StickyNoteForm form = null;

            foreach (var note in Program.User.StickyNotes)
            {
                form = ShowStickyNote(note);
            }

            if (form != null)
                form.Activate();

            tmrDetectRemind.Start();
        }

        TaskListForm _taskList;


        List<StickyNoteForm> _stickyNoteForms;

        /// <summary>
        /// For showing a new sticky note.
        /// </summary>
        /// <param name="task"></param>
        /// <returns></returns>
        internal StickyNoteForm ShowStickyNote(Task task, StickyNoteForm posRef)
        {
            StickyNote note = new StickyNote(task);

            Point loc;
            Size size = Program.User.Options.StickyNoteFormSize;

            if (posRef == null)
                posRef = ActiveStickyForm;

            if (posRef != null)
            {
                Screen screen = Screen.FromControl(this);
                int margin = 5;

                loc = new Point(posRef.Right + margin, posRef.Top);
                if (posRef.Left > screen.WorkingArea.Left + screen.WorkingArea.Width / 2)
                    loc.X = posRef.Left - size.Width - margin;
            }
            else
            {
                loc = new Point(size.Width / 3, size.Height / 3);
            }

            note.WindowBounds = new Rectangle(loc, size);
            Program.User.AddStickyNote(note);

            return ShowStickyNote(note);
        }

        public StickyNoteForm GetStickyForm(Task task)
        {
            return _stickyNoteForms.SingleOrDefault(o => o.Task == task);
        }

        internal StickyNoteForm ShowStickyNote(StickyNote note)
        {
            StickyNoteForm form = GetStickyForm(note.Task);

            if (form == null)
            {
                form = new StickyNoteForm(note);
                _stickyNoteForms.Add(form);

                form.Disposed += new EventHandler(StickyFormDisposed);
                form.KeyDown += new KeyEventHandler(StickyFormKeyDown);
                form.Activated += new EventHandler(StickyFormActivated);
                form.Deactivate += new EventHandler(StickyFormDeactive);
            }

            form.Show();
            return form;
        }

        void StickyFormDeactive(object sender, EventArgs e)
        {

            if (Form.ActiveForm == null)
            {
                Program.User.Persist();
                if (Program.User.Options.AutoCollapse)
                {
                    foreach (var form in _stickyNoteForms.ToArray())
                    {
                        if (form.Pinning)
                            form.FullSize = false;
                    }
                }
            }
        }

        public StickyNoteForm ActiveStickyForm
        {
            get
            {
                if (_stickyNoteForms.Count > 0)
                    return _stickyNoteForms[0];
                else
                    return null;
            }
        }

        void StickyFormActivated(object sender, EventArgs e)
        {
            var form = (StickyNoteForm)sender;

            lock (_stickyNoteForms)
            {
                int index = _stickyNoteForms.IndexOf(form);
                if (index > 0)
                {
                    _stickyNoteForms.RemoveAt(index);
                    _stickyNoteForms.Insert(0, form);

                }
            }
        }

        protected override void OnActivated(EventArgs e)
        {
            base.OnActivated(e);

            BringAllStickyNoteFormsToFront();
        }

        void StickyFormKeyDown(object sender, KeyEventArgs e)
        {
            StickyNoteForm form = (StickyNoteForm)sender;

            if (e.Alt && e.KeyCode == Keys.F4)
            {
                e.Handled = true;
                this.Close();
            }
            else if (e.Control && e.KeyCode == Keys.N)
            {
                e.Handled = true;
                this.NewStickyNote(form);
            }
            else if (e.Control && e.KeyCode == Keys.F4)
            {
                e.Handled = true;
                form.CloseStickyNote();
            }
            else
                base.OnKeyDown(e);
        }

        void StickyFormDisposed(object sender, EventArgs e)
        {
            StickyNoteForm form = (StickyNoteForm)sender;
            Guid id = form.Task.Id;

            _stickyNoteForms.Remove(form);

            if (form.StickNoteClosed)
                Program.User.DeleteStickyNote(id);
        }

        public StickyNoteForm NewStickyNote(StickyNoteForm reference)
        {
            Task task = Task.New(null, null);
            if (reference != null)
            {
                Task task0 = reference.Task;
                task.Category = task0.Category;
                task.Importance = task0.Importance;
            }
            Program.User.AddTask(task);
            return ShowStickyNote(task, reference);
        }

        private void tsmiNewTask_Click(object sender, EventArgs e)
        {
            NewStickyNote(null);
        }

        private void tsmiTaskList_Click(object sender, EventArgs e)
        {
            if (_taskList == null)
            {
                _taskList = new TaskListForm();

                _taskList.Disposed += (a, b) => { _taskList = null; };

            }

            _taskList.Show();

        }

        private void tsmiExit_Click(object sender, EventArgs e)
        {
            
            this.Close();
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
        }

        private void notifyIcon1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                BringAllStickyNoteFormsToFront();
            }

        }

        private void BringAllStickyNoteFormsToFront()
        {
            var array = _stickyNoteForms.ToArray().Reverse();
            this.Activate();

            foreach (var form in array)
            {
                form.FullSize = true;
                form.BringToFront();
            }
        }

        OptionsForm _optionsForm;

        private void tsmiOptions_Click(object sender, EventArgs e)
        {
            if (_optionsForm == null)
            {
                OptionsForm dlg = new OptionsForm();

                dlg.Applied += new EventHandler(OptionApplied);
                dlg.Disposed += (a, b) => { _optionsForm = null; };
                dlg.Show();

                _optionsForm = dlg;
            }

            _optionsForm.Activate();
        }

        void OptionApplied(object sender, EventArgs e)
        {
            OptionsForm optform = (OptionsForm)sender;

            foreach (var form in _stickyNoteForms)
            {
                form.ApplyUserOptions(optform.Options);
            }

            ApplyUserOptions(optform.Options);
        }

        private void ApplyUserOptions(UserOptions options)
        {
            RegisterHotKeys(options);
        }

        private void tmrDetectRemind_Tick(object sender, EventArgs e)
        {
            DateTime now = DateTime.Now;
            foreach (var form in _stickyNoteForms.ToArray())
            {
                if (form.Task.NeedsRemind && !form.IsReminding)
                {
                    var time = form.Task.RemindingTime.Value;
                    if (time < now) form.StartRemind();
                }
            }
        }
    }

}
