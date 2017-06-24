using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.ComponentModel;

namespace TaskBook.UI
{
    public class ToolButton : Button
    {
        public ToolButton()
            : base()
        {
            //SetStyle(ControlStyles.UserPaint, true);
            UseVisualStyleBackColor = false;
            
        }

        private ButtonState _state;

        public ButtonState State
        {
            get { return _state; }
            private set
            {
                if (_state != value)
                {
                    _state = value;
                    this.Invalidate();
                }
            }
        }

        protected override void OnMouseEnter(EventArgs e)
        {
            State = ButtonState.Flat;

            base.OnMouseEnter(e);

        }

        protected override void OnMouseLeave(EventArgs e)
        {
            State = ButtonState.Normal;

            base.OnMouseLeave(e);
        }

        protected override System.Drawing.Size DefaultSize
        {
            get
            {
                return new System.Drawing.Size(18, 18);
            }
        }

        private Size _imageSize;
        [DefaultValue(typeof(Size), "0,0")]
        public Size ImageSize
        {
            get { return _imageSize; }
            set { _imageSize = value; }
        }


        protected override void OnPaint(PaintEventArgs pevent)
        {
            bool flat = (this._state & ButtonState.Flat) == ButtonState.Flat;
            
            //base.OnPaint(pevent);

            Color color = this.BackColor;

            if (flat)
            {
                color = FlatAppearance.MouseOverBackColor;
                if (color.IsEmpty) color = SystemColors.ControlLightLight;
            }

            Brush br = new SolidBrush(color);

            Rectangle rect = new Rectangle(Point.Empty, this.Size), rect1 = rect;
            rect1.Width--; rect1.Height--;

            pevent.Graphics.FillRectangle(br, rect);
            br.Dispose();

            if (this.Image != null)
            {
                Image img = this.Image;
                Size size = _imageSize;
                if (size.IsEmpty) size = img.Size;
                Point pt = new Point( (Width - size.Width) / 2, (Height - size.Height) / 2);
                if (this.Enabled)
                    pevent.Graphics.DrawImage(img, new Rectangle(pt, size), new Rectangle(Point.Empty, img.Size), GraphicsUnit.Pixel);
                else
                    ControlPaint.DrawImageDisabled(pevent.Graphics, img, pt.X, pt.Y, Color.Empty);
            }

            if (flat)
            {
                color = FlatAppearance.BorderColor;
                if (color.IsEmpty) color = SystemColors.ControlLight;
                Pen pen = new Pen(color);
                pevent.Graphics.DrawRectangle(pen, rect1);
                pen.Dispose();
            }
        }
    }
}
