using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MouseKeyboardLibrary;

namespace TaskBook.UI
{
    public struct HotKey
    {
        private int _modifiers;

        public int Modifiers
        {
            get { return _modifiers; }
        }

        private Keys _keyCode;

        public Keys KeyCode
        {
            get { return _keyCode; }
            set { _keyCode = value; }
        }

        private bool _isExtendedKey;

        public bool IsExtendedKey
        {
            get { return _isExtendedKey; }
            set { _isExtendedKey = value; }
        }

        private int _scanCode;

        public int ScanCode
        {
            get { return _scanCode; }
            set { _scanCode = value; }
        }

        public void HookKeyStroke(KeyEventArgs e)
        {
            KeyCode = e.KeyCode;
            HookKeyEventArgs hke = (HookKeyEventArgs)e;
            IsExtendedKey = hke.IsExtendedKey;
            ScanCode = hke.ScanCode;
        }

        public bool Control
        {
            get { return (_modifiers & NativeMethods.MOD_CONTROL) == NativeMethods.MOD_CONTROL; }
            set { SetModifier(NativeMethods.MOD_CONTROL, value); }
        }

        public bool Alt
        {
            get { return (_modifiers & NativeMethods.MOD_ALT) == NativeMethods.MOD_ALT; }
            set { SetModifier(NativeMethods.MOD_ALT, value); }
        }

        public bool Shift
        {
            get { return (_modifiers & NativeMethods.MOD_SHIFT) == NativeMethods.MOD_SHIFT; }
            set { SetModifier(NativeMethods.MOD_SHIFT, value); }
        }

        public bool Win
        {
            get { return (_modifiers & NativeMethods.MOD_WIN) == NativeMethods.MOD_WIN; }
            set { SetModifier(NativeMethods.MOD_WIN, value); }
        }

        private void SetModifier(int mask, bool set)
        {
            if (set)
                _modifiers |= mask;
            else
                _modifiers &= ~mask;
        }

        internal void Clear()
        {
            _modifiers = 0;
            KeyCode = 0;
        }

        public string KeyText
        {
            get
            {
                if (_scanCode > 0)
                    return NativeMethods.GetKeyText(ScanCode, IsExtendedKey);
                else
                    return string.Empty;
            }
        }

        public override string ToString()
        {
            List<string> list = new List<string>();
            int modifiers = _modifiers;

            if ((modifiers & NativeMethods.MOD_WIN) > 0)
                list.Add("Win");

            if ((modifiers & NativeMethods.MOD_CONTROL) > 0)
                list.Add("Ctrl");

            if ((modifiers & NativeMethods.MOD_SHIFT) > 0)
                list.Add("Shift");

            if ((modifiers & NativeMethods.MOD_ALT) > 0)
                list.Add("Alt");

            if (KeyCode > 0)
                list.Add(KeyText);

            if (list.Count > 0)
                return string.Join(" + ", list.ToArray());
            else
                return string.Empty;
        }

        public bool IsEmpty
        {
            get { return _keyCode == Keys.None && _modifiers == 0; }
        }

        public int ToInt32()
        {
            int v = (int)_keyCode;

            v |= _modifiers << 16;
            v |= _scanCode << 20;
            if (_isExtendedKey)
                v |= 0x10000000;
            
            return v;
        }

        public HotKey(int data)
        {
            _keyCode = (Keys)(data & 0xffff);
            _modifiers = (data & 0xf0000) >> 16;
            _scanCode = (data & 0xff00000) >> 20;
            _isExtendedKey = (data & 0x10000000) > 0;
        }

        // override object.Equals
        public override bool Equals(object obj)
        {
            
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }

            return this.ToInt32() == ((HotKey)obj).ToInt32();
        }

        // override object.GetHashCode
        public override int GetHashCode()
        {
            return this.ToInt32();
        }
    }


}
