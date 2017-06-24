using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Drawing.Drawing2D;

namespace TaskBook.UI
{
    public partial class NCPaintForm : Form
    {
        const int WM_NCPAINT = 0x0085;
        private const int WM_NCACTIVATE = 0x0086;
        [DllImport("user32.dll")]
        private static extern IntPtr GetWindowDC(IntPtr hWnd);
        [DllImport("user32.dll")]
        private static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);
        public NCPaintForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        //int count;
        protected override void WndProc(ref Message m)
        {

            if (m.Msg == WM_NCPAINT || m.Msg == WM_NCACTIVATE)
            {
                if (m.Msg == WM_NCACTIVATE)
                    base.WndProc(ref m);

                IntPtr hdc = GetWindowDC(m.HWnd);
                Graphics g = Graphics.FromHdc(hdc);

                Size borderSize = SystemInformation.FrameBorderSize;
                Rectangle rect = new Rectangle(0,0,
                    Width, borderSize.Height + SystemInformation.ToolWindowCaptionHeight);
                //Region region = new System.Drawing.Region(rect);
                //rect = new Rectangle(
                //    borderSize.Width,
                //    borderSize.Height + SystemInformation.CaptionHeight,
                //    Width - borderSize.Width * 2,
                //    Height - borderSize.Height * 2 - SystemInformation.CaptionHeight);
                //region.Exclude(rect);
                //g.FillRegion(Brushes.Red, region);
                //region.Dispose();
                g.FillRectangle(Brushes.Red, rect);

                rect = new Rectangle(0, rect.Bottom, borderSize.Width, Height - rect.Bottom);
                g.FillRectangle(Brushes.Green, rect);
                rect.X = Width - borderSize.Width;
                g.FillRectangle(Brushes.Green, rect);
                rect = new Rectangle(borderSize.Width, Height - borderSize.Height, Width - borderSize.Width * 2, borderSize.Height);
                g.FillRectangle(Brushes.GreenYellow, rect);

                g.Dispose();
                ReleaseDC(m.HWnd, hdc);

            }
            else
                base.WndProc(ref m);
        }
    }
}
