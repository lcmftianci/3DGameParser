using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using TaskBook.Localization;

namespace TaskBook.UI
{
    public partial class OptionsForm : Form
    {
        public event EventHandler Applied;

        UserOptions _options;
        Dictionary<TaskImportance, ColorButton[]> _colorButtons;

        public OptionsForm()
        {
            InitializeComponent();

            _colorButtons = new Dictionary<TaskImportance, ColorButton[]>();
            var array = Enum.GetValues(typeof(TaskImportance));
            int y = lbBackColor.Bottom + 5;
            foreach (TaskImportance imp in array)
            {
                int row = _colorButtons.Count + 1;

                Label lb = new Label();
                lb.Text = LocaleInfo.Current.TranslateEnum(imp);
                lb.Location = new Point(10, y);
                ColorButton cb1 = new ColorButton(), cb2 = new ColorButton();
                cb1.Location = new Point(lbBackColor.Left, y);
                cb2.Location = new Point(lbCaptionColor.Left, y);

                _colorButtons.Add(imp, new [] { cb1, cb2});
                gbColors.Controls.AddRange(new Control[] { lb, cb1, cb2 });
                y += cb1.Height + 5;
            }

            _options = Program.User.Options;
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            Bind(_options);
        }

        public UserOptions Options
        {
            get { return _options; }
        }

        private void Bind(UserOptions options)
        {
            chkAutoCollapse.Checked = options.AutoCollapse;
            chkAutoExpand.Checked = options.AutoExpand;
            nudOpacity.Value = (decimal)(options.CollapsedOpacity / 2.55);
            bnFont.Font = options.DefaultFont;
            nudHeight.Value = options.StickyNoteFormSize.Height;
            nudWidth.Value = options.StickyNoteFormSize.Width;

            foreach (TaskImportance imp in Enum.GetValues(typeof(TaskImportance)))
            {
                var theme = options.GetImportanceTheme(imp);
                var buttons = _colorButtons[imp];
                buttons[0].SelectedColor = theme.BackColor;
                buttons[1].SelectedColor = theme.CaptionBackColor;
            }

            hktbAddNew.HotKey = options.GetHotKey(HotKeyType.AddNewStickyNote);
            hktbShowAll.HotKey = options.GetHotKey(HotKeyType.ShowAllStickyNotes);
        }

        private void Apply(UserOptions options)
        {
            options.AutoCollapse = chkAutoCollapse.Checked;
            options.AutoExpand = chkAutoExpand.Checked;
            options.CollapsedOpacity = (byte)(nudOpacity.Value / 100 * 255);
            options.DefaultFont = bnFont.Font;
            options.StickyNoteFormSize = new Size((int)nudWidth.Value, (int)nudHeight.Value);

            foreach (TaskImportance imp in Enum.GetValues(typeof(TaskImportance)))
            {
                var theme = options.GetImportanceTheme(imp);
                var buttons = _colorButtons[imp];
                theme.BackColor = buttons[0].SelectedColor;
                theme.CaptionBackColor = buttons[1].SelectedColor;
            }

            options.HotKeys[HotKeyType.ShowAllStickyNotes] = hktbShowAll.HotKey;
            options.HotKeys[HotKeyType.AddNewStickyNote] = hktbAddNew.HotKey;

            if (Applied != null)
                Applied(this, EventArgs.Empty);
        }

        private void apply_Click(object sender, EventArgs e)
        {
            Apply(_options);
        }

        private void ok_Click(object sender, EventArgs e)
        {
            Apply(_options);
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Close();
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Close();
        }

        private void resetThemes_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(this, "确定要将所有的颜色都还原为默认值吗？", ProductName, MessageBoxButtons.OKCancel, MessageBoxIcon.Question)
                == System.Windows.Forms.DialogResult.OK)
            {
                foreach (TaskImportance imp in Enum.GetValues(typeof(TaskImportance)))
                {
                    var theme = UserOptions.DefaultImportanceThemes[imp];
                    var buttons = _colorButtons[imp];
                    buttons[0].SelectedColor = theme.BackColor;
                    buttons[1].SelectedColor = theme.CaptionBackColor;
                }
            }

        }
    }

    class ColorButton : Button
    {
        public ColorButton()
        {
            
        }

        protected override void OnPaint(PaintEventArgs pevent)
        {
            base.OnPaint(pevent);

            Rectangle rect = new Rectangle(Point.Empty, this.Size);

            rect.Inflate(-5, -5);

            SolidBrush br = new SolidBrush(_selectedColor);
            pevent.Graphics.FillRectangle(br, rect);

            br.Dispose();
        }

        private Color _selectedColor;

        public Color SelectedColor
        {
            get { return _selectedColor; }
            set
            { 
                _selectedColor = value;
                if (IsHandleCreated)
                    this.Invalidate();
            }
        }

        protected override void OnClick(EventArgs e)
        {
            ColorDialog dlg = new ColorDialog();
            dlg.Color = _selectedColor;
            if (dlg.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                SelectedColor = dlg.Color;
            }
        }
        
    }

    class FontButton : Button
    {
        public FontButton()
        {

        }

        protected override void OnFontChanged(EventArgs e)
        {
            base.OnFontChanged(e);

            this.Text = string.Format("{0}, {1}pt", Font.Name, Font.SizeInPoints);
        }

        protected override void OnClick(EventArgs e)
        {
            FontDialog dlg = new FontDialog();
            dlg.Font = this.Font;

            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Font = dlg.Font;
            }
        }
    }
}
