using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using TaskBook.Localization;

namespace TaskBook.UI
{
    public partial class StickyNoteForm : Form
    {
        public event EventHandler DirtyChanged;

        private const int BORDER_SIZE = 4;
        private const int CAPTION_HEIGHT = 24;

        private readonly Size MinSize, MinSizeFS;

        private static readonly DataFormats.Format DataFormat_Text = DataFormats.GetFormat(DataFormats.Text);
        private static readonly DataFormats.Format DataFormat_Rtf = DataFormats.GetFormat(DataFormats.Rtf);

        StickyNote _note;
        ControlSet _toolButtons;
        ToolStripMenuItem[] _importanceMenus;
        bool _dirty;

        public StickyNoteForm(StickyNote note)
            : this()
        {
            if (note == null)
                throw new ArgumentNullException("note");

            this.StartPosition = FormStartPosition.Manual;
            Rectangle rect = note.WindowBounds;
            if (!rect.IsEmpty) this.Bounds = rect;

            _note = note;
            Task task = note.Task;

            richTextBox1.Font = Program.User.Options.DefaultFont;
            string text = task.Contents, rtf = task.ContentsRtf;

            if (!string.IsNullOrEmpty(text))
            {
                if (rtf != null)
                {
                    try { richTextBox1.Rtf = rtf; }
                    catch
                    {
                        richTextBox1.Text = text;
                    }
                }
                else
                    richTextBox1.Text = text;
            }
            richTextBox1.ScrollBars = note.Overflow ? RichTextBoxScrollBars.Both : RichTextBoxScrollBars.None;
            richTextBox1.TextChanged += new EventHandler(richTextBox1_TextChanged);
            richTextBox1.ContentsResized += new ContentsResizedEventHandler(richTextBox1_ContentsResized);
            richTextBox1.SizeChanged += new EventHandler(richTextBox1_SizeChanged);

            task.PropertyChanged += new PropertyChangedEventHandler(TaskPropertyChanged);

            SetImportance(task.Importance);

            Pinning = note.Pinning;

            UpdateApparence();
        }

        protected override void OnFormClosed(FormClosedEventArgs e)
        {
            base.OnFormClosed(e);

            if (_note != null)
            {
                _note.Task.PropertyChanged -= new PropertyChangedEventHandler(TaskPropertyChanged);
            }
        }

        void TaskPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            string name = e.PropertyName;
            Dirty = true;

            switch (name)
            {
                case "Importance":
                    this.SetImportance(((Task)sender).Importance);
                    break;
                case "RemindingTime":
                case "Reminded":
                case "Finished":
                    UpdateApparence();
                    break;
            }
        }

        public bool Dirty
        {
            get { return _dirty; }
            private set
            {
                if (_dirty != value)
                {
                    _dirty = value;
                    if (DirtyChanged != null)
                        DirtyChanged(this, EventArgs.Empty);
                }
            }
        }

        private void SetImportance(TaskImportance value)
        {
            foreach (var mi in _importanceMenus)
            {
                mi.Checked = value == (TaskImportance)mi.Tag;
            }

            if (value != TaskImportance.Memo && !Task.Finished)
            {
                if (!_toolButtons.Contains(tbFinish))
                {
                    tbFinish.Visible = _toolButtons.Visible;
                    _toolButtons.Add(tbFinish);
                }
            }
            else
            {
                tbFinish.Visible = false;
                _toolButtons.Remove(tbFinish);
            }
            ApplyUserOptions();
        }

        void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            this.Task.Contents = richTextBox1.Text;
            this.Task.ContentsRtf = richTextBox1.Rtf;
        }


        private StickyNoteForm()
        {
            InitializeComponent();

            _toolButtons = new ControlSet();
            _toolButtons.Add(tbFinish);
            _toolButtons.Add(tbNew);
            _toolButtons.Add(tbRemind);
            _toolButtons.Add(tbPin);

            List<ToolStripMenuItem> list = new List<ToolStripMenuItem>();
            foreach (TaskImportance imp in Enum.GetValues(typeof(TaskImportance)))
            {
                ToolStripMenuItem mi = new ToolStripMenuItem(
                    LocaleInfo.Current.TranslateEnum(imp),
                    (Image)Properties.Resources.ResourceManager.GetObject("importance_" + imp.ToString().ToLower()));
                mi.Tag = imp;
                mi.Click += new EventHandler(ImportanceMenuItemClick);
                contextMenuStrip1.Items.Insert(list.Count, mi);
                list.Add(mi);

            }

            _importanceMenus = list.ToArray();

            pnTitle.Bounds = new Rectangle(
               BORDER_SIZE,
               BORDER_SIZE,
               this.Width - BORDER_SIZE * 2,
               CAPTION_HEIGHT);

            richTextBox1.Bounds = new Rectangle(
                 BORDER_SIZE,
                 pnTitle.Bottom,
                 this.Width - BORDER_SIZE * 2,
                 this.Height - pnTitle.Bottom - BORDER_SIZE);

            MinSizeFS = this.MinimumSize;
            MinSize = new Size(MinSizeFS.Width, BORDER_SIZE * 2 + CAPTION_HEIGHT);

            this.Size = Program.User.Options.StickyNoteFormSize;


            NativeMethods.EnableWindowDropShandow(this);
        }

        protected override CreateParams CreateParams
        {
            get
            {
                var cp = base.CreateParams;

                cp.ExStyle |= 0x80;      //WS_EX_TOOLWINDOW

                return cp;
            }
        }

        void ImportanceMenuItemClick(object sender, EventArgs e)
        {
            ToolStripMenuItem mi = (ToolStripMenuItem)sender;
            TaskImportance imp = (TaskImportance)mi.Tag;

            if (imp != Task.Importance)
            {
                Task.Importance = imp;
            }
            
        }

        public Task Task
        {
            get { return _note.Task; }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            ApplyUserOptions();
            SaveNoteSettings();
        }


        private void richTextBox1_SelectionChanged(object sender, EventArgs e)
        {
            //Font font = richTextBox1.SelectionFont;
            //if (font != null)
            //{
            //    tsbBold.Checked = font.Bold;
            //    tsbItalic.Checked = font.Italic;
            //    tsbUnderline.Checked = font.Underline;

            //}

        }


        //private void ChangeSelectionFontStyle(FontStyle type, bool set)
        //{
        //    Font font0 = richTextBox1.SelectionFont;
        //    int style = (int)font0.Style & ~((int)type);

        //    if (set) style |= (int)type;

        //    Font font1 = new Font(font0, (FontStyle)style);

        //    richTextBox1.SelectionFont = font1;
        //    font0.Dispose();

        //}


        private void ClipboardAction(object sender, EventArgs e)
        {
            string action = (string)((ToolStripMenuItem)sender).Tag;
            string arg;
            var type = richTextBox1.SelectionType;
            
            int p = action.IndexOf('.');
            if (p > 0)
            {
                arg = action.Substring(p + 1);
                action = action.Substring(0, p);
            }
            else
                arg = null;
            
            switch (action)
            {
                case "paste":
                    var fmt = DataFormat_Rtf;
                    
                    if (arg == "plain")
                    {
                        fmt = DataFormat_Text;
                    }
                    
                    if (richTextBox1.CanPaste(fmt))
                        richTextBox1.Paste(fmt);
                    break;
                case "copy":
                    richTextBox1.Copy();
                    break;
                case "cut":
                    richTextBox1.Cut();
                    break;
            }
        }

        private void tsmiFont_Click(object sender, EventArgs e)
        {
            FontDialog dlg = new FontDialog();
            dlg.Font = richTextBox1.SelectionFont;
            dlg.ShowColor = true;
            dlg.Color = richTextBox1.SelectionColor;
            if (dlg.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                Font font = dlg.Font;
                richTextBox1.SelectionFont = dlg.Font;
                richTextBox1.SelectionColor = dlg.Color;
                font.Dispose();
            }
        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            var seltype = richTextBox1.SelectionType;
            bool fullSize = FullSize;

            tsmiCut.Enabled = tsmiCopy.Enabled = tsmiFont.Enabled =
                seltype != RichTextBoxSelectionTypes.Empty && fullSize;

            tsmiPaste.Enabled = fullSize && richTextBox1.CanPaste(DataFormat_Rtf); //Clipboard.ContainsText() || Clipboard.ContainsText(TextDataFormat.Rtf);
            tsmiPastePlain.Enabled = fullSize && richTextBox1.CanPaste(DataFormat_Text);
            tsmiFinishAndClose.Enabled = Task.Importance != TaskImportance.Memo && !Task.Finished;
        }


        DraggingInfo _dragging;

        private void pnTitle_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                _dragging = new DraggingInfo(this, MouseAction.Move);
                _dragging.Start(e);
            }
            
        }

        private void pnTitle_MouseMove(object sender, MouseEventArgs e)
        {
            if (_dragging.HasStarted(MouseAction.Move))
            {
                _dragging.Update(e);
            }
        }

        private void pnTitle_MouseUp(object sender, MouseEventArgs e)
        {
            if (_dragging.HasStarted(MouseAction.Move))
                _dragging.End();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Rectangle rect;
            
            //rect = this.ClientRectangle;
            //Pen pen = new Pen(pnTitle.BackColor);
            //e.Graphics.DrawRectangle(pen, rect.X, rect.Y, rect.Width - 1, rect.Height - 1);

            //pen.Dispose();

            Color color;
            color = pnTitle.BackColor;

            rect = new Rectangle(0, 0, this.Width, CAPTION_HEIGHT + BORDER_SIZE);
            SolidBrush br = new SolidBrush(color);
            e.Graphics.FillRectangle(br, rect);
            br.Dispose();

            //int w = Width - richTextBox1.Right;
            //int h = Height - richTextBox1.Bottom;

            //rect = new Rectangle(richTextBox1.Right, richTextBox1.Bottom, w, h);
            //ControlPaint.DrawSizeGrip(e.Graphics, ControlPaint.Dark(pnTitle.BackColor), rect);

            base.OnPaint(e);
        }

        protected override void OnActivated(EventArgs e)
        {
            base.OnActivated(e);

            if (FullSize)
                _toolButtons.Visible = true;
            else if (Program.User.Options.AutoExpand)
            {
                FullSize = true;
                pnTitle_MouseEnter(this, e);
            }

            // 如果不使用BeginInvoke，richTextBox1就无法获得焦点。
            if (!richTextBox1.Focused)
                this.BeginInvoke(new Action(() => richTextBox1.Focus()));
        }

        protected override void OnDeactivate(EventArgs e)
        {
            base.OnDeactivate(e);

            _toolButtons.Visible = false;
        }

        private void pnTitle_MouseEnter(object sender, EventArgs e)
        {
            if (FullSize)
                _toolButtons.Visible = true;

        }

        private void pnTitle_MouseLeave(object sender, EventArgs e)
        {

            if (this != Form.ActiveForm)
            {
                Point loc = Control.MousePosition;
                loc = pnTitle.Parent.PointToClient(loc);

                if (!pnTitle.Bounds.Contains(loc))
                {
                    _toolButtons.Visible = false;
                }
            }
        }

        private void toolButton1_Click(object sender, EventArgs e)
        {
            Program.MainForm.NewStickyNote(this);
        }

        private void tsmiQuit_Click(object sender, EventArgs e)
        {
            Program.MainForm.Close();
        }

        private void BoundsChanged(object sender, EventArgs e)
        {
            SaveNoteSettings();
        }

        private void SaveNoteSettings()
        {
            if (_note != null)
            {
                Size size;

                size = this.Size;
                if (!FullSize) size.Height = _note.WindowBounds.Height;
                _note.WindowBounds = new Rectangle(this.Location, size);

                _note.Overflow = richTextBox1.ScrollBars != RichTextBoxScrollBars.None;
            }
        }

        internal bool Pinning
        {
            get
            {
                return _note.Pinning;
            }
            set
            {
                _note.Pinning = this.TopMost = value;
                UpdateApparence();
            }
        }

        private void UpdateApparence()
        {
            if (!this.IsDisposed)
            {
                Task task = this.Task;

                tbPin.Image = Pinning ? Properties.Resources.pin : Properties.Resources.pin_gray;
                tbRemind.Image = task.NeedsRemind ? Properties.Resources.Reminder : Properties.Resources.Reminder_gray;

                string text;
                if (task.NeedsRemind)
                {
                    if (IsReminding) text = "点击以停止提醒";
                    else text = string.Format("将在{0:f}进行提醒，点击以更改提醒设置。", task.RemindingTime);
                }
                else
                    text = "点击进行提醒设置";

                toolTip1.SetToolTip(tbRemind, text);

                text = Pinning ? "此便签已置顶，点击以取消。" : "将便签置于顶层";
                toolTip1.SetToolTip(tbPin, text);
            }
        }

        private void pnTitle_Paint(object sender, PaintEventArgs e)
        {
            if (Pinning)
            {
                if (!FullSize)
                {
                    var rect = new Rectangle(Point.Empty, pnTitle.Size);

                    rect.Inflate(-2, -2);
                    
                    TextRenderer.DrawText(e.Graphics, richTextBox1.Text, pnTitle.Font, rect, Color.Black,
                        TextFormatFlags.VerticalCenter | TextFormatFlags.Left | TextFormatFlags.EndEllipsis);
                }
                else
                {
                }
            }
        }

        private void pnTitle_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (Pinning)
            {
                FullSize = !FullSize;
                pnTitle_MouseEnter(sender, e);
            }
        }

        internal bool FullSize
        {
            get
            {
                return richTextBox1.Visible;
            }
            set
            {
                if (FullSize != value)
                {
                    if (value)
                    {
                        richTextBox1.Visible = true;
                        this.Size = _note.WindowBounds.Size;
                        this.MinimumSize = MinSizeFS;
                    }
                    else
                    {
                        this.MinimumSize = MinSize;

                        richTextBox1.Visible = false;
                        this.Height = MinSize.Height;
                        _toolButtons.Visible = false;

                    }

                    ApplyUserOptions();
                }
            }
        }

        private void tbExpand_Click(object sender, EventArgs e)
        {
            FullSize = true;
        }

        private void ApplyUserOptions()
        {
            ApplyUserOptions(Program.User.Options);
        }

        internal void ApplyUserOptions(UserOptions options)
        {
            this.Opacity = FullSize ? 1.0 : options.CollapsedOpacity / 255.0;
            
            var theme = options.GetImportanceTheme(Task.Importance);

            pnTitle.BackColor = theme.CaptionBackColor;
            this.BackColor = richTextBox1.BackColor = theme.BackColor;

            if (this.IsHandleCreated)
            {
                this.Invalidate();
                pnTitle.Invalidate();
            }
        }

        Rectangle _rtb_contents_bounds;

        private void richTextBox1_ContentsResized(object sender, ContentsResizedEventArgs e)
        {
            RichTextBox rtb = (RichTextBox)sender;
            if (rtb.ScrollBars == RichTextBoxScrollBars.None)
            {
                Size size0 = rtb.ClientSize, size1 = e.NewRectangle.Size;
                if (!_dragging.HasStarted(MouseAction.SizeMask))
                {
                    if (size1.Height > size0.Height)
                    {
                        int height = this.Height + size1.Height - size0.Height;
                        Screen screen = Screen.FromControl(this);
                        if (height + this.Top >= screen.WorkingArea.Bottom)
                        {
                            rtb.ScrollBars = RichTextBoxScrollBars.Both;
                            height = screen.WorkingArea.Bottom - this.Top;
                        }
                        this.Height = height;
                    }
                }
                else
                    rtb.ScrollBars = size1.Height > size0.Height ?
                        RichTextBoxScrollBars.Both : RichTextBoxScrollBars.None;
            }
            _rtb_contents_bounds = e.NewRectangle;
        }

        private void richTextBox1_SizeChanged(object sender, EventArgs e)
        {
            try
            {
                if (richTextBox1.ClientSize.Height < _rtb_contents_bounds.Height)
                {
                    if (_dragging.HasStarted(MouseAction.SizeMask))
                        richTextBox1.ScrollBars = RichTextBoxScrollBars.Both;
                }
                else
                    richTextBox1.ScrollBars = RichTextBoxScrollBars.None;

                SaveNoteSettings();
            }
            catch (Win32Exception)
            {
            }
        }

        MouseAction _sizingAction;

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

            if (_sizingAction != MouseAction.None && !_dragging.Started)
            {
                _dragging = new DraggingInfo(this, _sizingAction);
                _dragging.Start(e);
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);

            if (_dragging.HasStarted(MouseAction.SizeMask))
                _dragging.End();
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);

            if (!_dragging.Started)
            {
                int x = e.X, y = e.Y;
                Rectangle rect = new Rectangle(Point.Empty, this.Size);

                rect.Inflate(-BORDER_SIZE, -BORDER_SIZE);
                MouseAction action = MouseAction.None;

                if (!rect.Contains(e.Location))
                {
                    if (FullSize)
                    {
                        if (y < rect.Top)
                            action |= MouseAction.SizeN;
                        else if (y >= rect.Bottom)
                            action |= MouseAction.SizeS;
                    }

                    if (x < rect.Left)
                        action |= MouseAction.SizeW;
                    else if (x >= rect.Right)
                        action |= MouseAction.SizeE;
                }

                if (action != _sizingAction)
                {
                    Cursor cursor;

                    if (action == MouseAction.SizeN || action == MouseAction.SizeS)
                        cursor = Cursors.SizeNS;
                    else if (action == MouseAction.SizeW || action == MouseAction.SizeE)
                        cursor = Cursors.SizeWE;
                    else if (action == MouseAction.SizeNW || action == MouseAction.SizeSE)
                        cursor = Cursors.SizeNWSE;
                    else if (action == MouseAction.SizeNE || action == MouseAction.SizeSW)
                        cursor = Cursors.SizeNESW;
                    else
                        cursor = Cursors.Default;

                    this.Cursor = cursor;
                    _sizingAction = action;
                }
            }
            else if (_dragging.HasStarted(MouseAction.SizeMask))
            {
                _dragging.Update(e);
            }
        }

        private void richTextBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.V && e.Control ||
                e.KeyCode == Keys.Insert && e.Shift)
            {
                ClipboardAction(tsmiPaste, e);
                e.Handled = true;
            }
        }

        private void tbRemind_Click(object sender, EventArgs e)
        {
            ContextMenuStrip menu;
            if (!IsReminding)
            {
                menu = mnuSetRemindTime;
            }
            else
            {
                menu = mnuStopRemind;
            }

            menu.Show(tbRemind, 0, tbRemind.Height);
        }

        private bool _stickyNoteClosed;

        public bool StickNoteClosed
        {
            get { return _stickyNoteClosed; }
        }

        private void CloseStickyNoteInternal()
        {
            _stickyNoteClosed = true;
            this.Close();
        }

        public bool CloseStickyNote()
        {
            if (HasContents)
            {
                DialogResult dr = System.Windows.Forms.DialogResult.OK;
                if (Task.RemindingTime != null && !Task.Reminded)
                {
                    dr = MessageBox.Show(this, "此任务已设置提醒，但未到提醒时间。如果此时关闭此便签，将无法收到提醒的通知！确定要关闭吗？",
                        ProductName, MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2);
                }

                if (dr == System.Windows.Forms.DialogResult.OK)
                {
                    this.CloseStickyNoteInternal();
                    return true;
                }
            }
            else
            {
                Program.User.DeleteTask(Task);
                return true;
            }

            return false;
        }

        private void tsmiClose_Click(object sender, EventArgs e)
        {
            CloseStickyNote();
        }

        private void tsmiFinishAndClose_Click(object sender, EventArgs e)
        {
            this.Task.Finished = true;
            this.CloseStickyNoteInternal();
        }

        private void tsmiDeleteTask_Click(object sender, EventArgs e)
        {
            if (!HasContents || MessageBox.Show(this, "确定要删除此任务吗？", ProductName, MessageBoxButtons.OKCancel, MessageBoxIcon.Question)
                 == System.Windows.Forms.DialogResult.OK)
            Program.User.DeleteTask(Task);
        }

        public bool HasContents
        {
            get
            {
                return richTextBox1.TextLength > 0;
            }
        }

        private void tbPin_Click(object sender, EventArgs e)
        {
            this.Pinning = !this.Pinning;
        }

        public bool IsReminding
        {
            get { return tmrRemind.Enabled; }
        }

        public void StartRemind()
        {
            if (!IsReminding)
            {
                this.TopMost = true;
                this.FullSize = true;
                tbRemind.ImageSize = new System.Drawing.Size(16, 16);
                tmrRemind.Start();
            }
        }

        public void StopRemind(TimeSpan postpone)
        {
            Task task = Task;

            if (!task.Reminded)
            {
                if (postpone == TimeSpan.Zero)
                    task.Reminded = true;
                else
                    task.RemindingTime = DateTime.Now + postpone;
            }

            if (IsReminding)
            {
                if (!Pinning) this.TopMost = false;
                tbRemind.ImageSize = new System.Drawing.Size(12, 12);
                ApplyUserOptions();
                tmrRemind.Stop();
            }
        }

        private void tmrRemind_Tick(object sender, EventArgs e)
        {
            if (tmrRemind.TickCount % 2 == 1)
                pnTitle.BackColor = Color.Red;
            else
                pnTitle.BackColor = Program.User.Options.GetImportanceTheme(_note.Task.Importance).CaptionBackColor;
            this.Invalidate();
        }

        private void mnuStopRemind_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            ToolStripMenuItem mi = e.ClickedItem as ToolStripMenuItem;

            if (mi != null)
            {
                string text = (string)mi.Tag;
                TimeSpan postpone;

                if (!string.IsNullOrEmpty(text))
                {
                    if (!TimeSpan.TryParse(text, out postpone))
                        return;
                }
                else
                    postpone = TimeSpan.Zero;

                StopRemind(postpone);
            }
        }

        private void mnuSetRemindTime_Opening(object sender, CancelEventArgs e)
        {
            tsmiClearReminding.Enabled = Task.RemindingTime != null;
        }

        private void mnuSetRemindTime_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            ToolStripMenuItem mi = e.ClickedItem as ToolStripMenuItem;

            if (mi == tsmiClearReminding)
            {
                Task.RemindingTime = null;
            }
            else if (mi != null)
            {
                string text = (string)mi.Tag;
                if (text == "Custom")
                {
                    RemindingTimeForm dlg = new RemindingTimeForm();
                    dlg.Value = Task.RemindingTime ?? DateTime.Now.AddMinutes(10);
                    if (dlg.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
                        Task.RemindingTime = dlg.Value;
                }
                else
                {
                    TimeSpan after;

                    if (!string.IsNullOrEmpty(text))
                    {
                        if (TimeSpan.TryParse(text, out after))
                        {
                            Task.RemindingTime = DateTime.Now + after;
                        }
                    }
                }
            }

        }
    }

    class RemindTimer : Timer
    {
        public RemindTimer()
        {

        }

        public override bool Enabled
        {
            get
            {
                return base.Enabled;
            }
            set
            {
                base.Enabled = value;
                if (value) _tickCount = 0;
            }
        }

        protected override void OnTick(EventArgs e)
        {
            _tickCount++;
            base.OnTick(e);
        }

        private long _tickCount;
        [Browsable(false)]
        public long TickCount
        {
            get { return _tickCount; }
        }

    }

    class ControlSet : List<Control>
    {
        public ControlSet()
        {

        }

        public bool Visible
        {
            get
            {
                if (Count > 0) return this[0].Visible;
                else return false;
            }
            set
            {
                foreach (var ctl in this)
                {
                    ctl.Visible = value;
                }
            }
        }
    }

    enum MouseAction
    {
        None = 0,
        Move = 0x10,
        SizeN = 0x08,
        SizeS = 0x02,
        SizeW = 0x04,
        SizeE = 0x01,
        SizeNW = SizeN + SizeW,
        SizeNE = SizeN + SizeE,
        SizeSW = SizeS + SizeW,
        SizeSE = SizeS + SizeE,
        SizeMask = SizeNW | SizeNE | SizeSW | SizeSE
    }


        struct DraggingInfo
        {
            public DraggingInfo(Control target, MouseAction action)
            {
                if (action == MouseAction.None)
                    throw new ArgumentException("Action cannot be None.");

                _target = target;
                _x = _y = 0;
                _started = false;
                _action = action;
            }

            private bool _started;
            private int _x;
            private int _y;
            private Control _target;
            private MouseAction _action;

            public bool Started
            {
                get { return _started; }
            }

            public MouseAction Action
            {
                get { return _action; }
            }

            public bool HasStarted(MouseAction action)
            {
                return _started && (_action & action) > MouseAction.None;
            }

            public int X
            {
                get { return _x; }
            }

            public int Y
            {
                get { return _y; }
            }

            public void Start(MouseEventArgs e)
            {
                _started = true;
                _x = e.X;
                _y = e.Y;
            }

            public void Update(MouseEventArgs e)
            {
                if (_started && _action != MouseAction.None)
                {
                    if (_target != null)
                    {
                        if (_action == MouseAction.Move)
                        {
                            Point loc = _target.Location;
                            loc.Offset(e.X - _x, e.Y - _y);
                            _target.Location = loc;
                        }
                        else
                        {
                            Rectangle bounds = _target.Bounds;
                            int diffX = e.X - _x, diffY = e.Y - _y;
                            MouseAction tmp;

                            tmp = _action & (MouseAction.SizeE | MouseAction.SizeW);

                            if (tmp != MouseAction.None)
                            {
                                bounds.Width += diffX;
                                if (tmp == MouseAction.SizeW)
                                {
                                    bounds.Offset(diffX, 0);
                                    bounds.Width -= diffX * 2;
                                }
                                else
                                    _x = e.X;
                            }

                            tmp = _action & (MouseAction.SizeN | MouseAction.SizeS);

                            if (tmp != MouseAction.None)
                            {
                                bounds.Height += diffY;
                                if (tmp == MouseAction.SizeN)
                                {
                                    bounds.Offset(0, diffY);
                                    bounds.Height -= diffY * 2;
                                }
                                else
                                    _y = e.Y;
                            }

                            _target.Bounds = bounds;
                            //_x = e.X;
                            //_y = e.Y;
                        }
                    }

                    
                }
            }

            public void End()
            {
                if (_started)
                {
                    _started = false;
                    _x = _y = 0;
                }
            }
        }

}
