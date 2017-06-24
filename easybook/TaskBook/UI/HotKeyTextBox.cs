using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MouseKeyboardLibrary;
using System.Runtime.InteropServices;
using System.Drawing;

namespace TaskBook.UI
{
    public class HotKeyTextBox : TextBox
    {
        KeyboardHook _hook;

        public HotKeyTextBox()
        {
            _keys = new List<Keys>();
            _hook = new KeyboardHook();
            
            _hook.KeyDown += new KeyEventHandler(_hook_KeyDown);
            _hook.KeyUp += new KeyEventHandler(_hook_KeyUp);
            
        }

        void _hook_KeyUp(object sender, KeyEventArgs e)
        {
            _keys.Remove(e.KeyCode);

            e.Handled = true;
            e.SuppressKeyPress = true;
        }

        void _hook_KeyDown(object sender, KeyEventArgs e)
        {
            if (_keys.Count == 0)
                _hotKey.Clear();

            if (!_keys.Contains(e.KeyCode))
            {
                if (e.KeyCode == Keys.Escape && e.Modifiers == Keys.None)
                {
                    _keys.Clear();
                }
                else
                {
                    switch (e.KeyCode)
                    {
                        case Keys.ShiftKey:
                        case Keys.LShiftKey:
                        case Keys.RShiftKey:
                            _hotKey.Shift = true;
                            break;
                        case Keys.ControlKey:
                        case Keys.LControlKey:
                        case Keys.RControlKey:
                            _hotKey.Control = true;
                            break;
                        case Keys.Menu:
                        case Keys.LMenu:
                        case Keys.RMenu:
                            _hotKey.Alt = true;
                            break;
                        case Keys.LWin:
                        case Keys.RWin:
                            _hotKey.Win = true;
                            break;
                        default:
                            _hotKey.HookKeyStroke(e);
                            break;
                    }

                    _keys.Add(e.KeyCode);
                }

                UpdateKeyText();
            }

            e.Handled = true;
            e.SuppressKeyPress = true;
        }

        private HotKey _hotKey;

        public HotKey HotKey
        {
            get { return _hotKey; }
            set
            {
                if (!_hotKey.Equals(value))
                {
                    if (_keys.Count > 0)
                        throw new InvalidOperationException("Not avalibale.");
                    _hotKey = value;
                    UpdateKeyText();
                }
            }
        }

        private List<Keys> _keys;

        protected override void OnGotFocus(EventArgs e)
        {
            base.OnGotFocus(e);
            _keys.Clear();
            _hook.Start();
            if (!_hook.IsStarted)
                this.BackColor = Color.Red;
        }

        protected override void OnLostFocus(EventArgs e)
        {
            base.OnLostFocus(e);
            _hook.Stop();
        }

        private void UpdateKeyText()
        {
            if (_hotKey.IsEmpty)
                this.Text = "None";
            else
                this.Text = _hotKey.ToString();
            //this.Text = new HotKey(_hotKey.ToInt32()).ToString();
        }

    }

}
