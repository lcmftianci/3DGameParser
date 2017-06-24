using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace TaskBook.UI
{
    internal static class NativeMethods
    {
        public const int CS_DROPSHADOW = 0x20000;
        public const int GCL_STYLE = (-26);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern int SetClassLong(IntPtr hwnd, int nIndex, int dwNewLong);
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern int GetClassLong(IntPtr hwnd, int nIndex);

        public static void EnableWindowDropShandow(IWin32Window window)
        {
            SetClassLong(window.Handle, GCL_STYLE, GetClassLong(window.Handle, GCL_STYLE) | CS_DROPSHADOW);
        }

        
        public const int MOD_ALT = 1;
        public const int MOD_CONTROL = 2;
        public const int MOD_SHIFT = 4;
        public const int MOD_WIN = 8;

        public const int WM_HOTKEY = 0x0312;

        [DllImport("user32.dll")]
        public static extern bool RegisterHotKey(IntPtr hWnd, int id, int fsModifiers, int vk);

        [DllImport("user32.dll")]
        public static extern bool UnregisterHotKey(IntPtr hWnd, int id);

        [DllImport("user32.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Winapi)]
        private static extern int GetKeyNameText(IntPtr lParam, StringBuilder name, int cchSize);

        public static string GetKeyText(int scanCode, bool isExtendedKey)
        {
            StringBuilder sb = new StringBuilder(256);
            int p = scanCode << 16;
            if (isExtendedKey) p = p | 0x1000000;
            p = GetKeyNameText((IntPtr)(p + 1), sb, 256);

            return sb.ToString(0, p);
        }


    }
}
