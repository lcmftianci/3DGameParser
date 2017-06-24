using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.IO;

namespace TaskBook
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            string path;

#if DEBUG
            path = "c:\\temp\\taskbook.xml";
#else
            path = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "TaskBook");
            if (!Directory.Exists(path)) Directory.CreateDirectory(path);
            path = Path.Combine(path, "userdata.xml");
            Console.WriteLine(path);
#endif

            _user = UserContext.Load(path);
            _mainForm = new UI.MainForm();

            Application.Run(_mainForm);

            _user.Persist();
        }

        static UI.MainForm _mainForm;

        public static UI.MainForm MainForm
        {
            get
            {
                return _mainForm;
            }
        }

        static UserContext _user;

        public static UserContext User
        {
            get
            {
                return _user;
            }
        }
    }
}
