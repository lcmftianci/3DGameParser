using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml.Linq;
using System.ComponentModel;

namespace TaskBook
{
    public class StickyNote
    {
        public StickyNote(Task task)
        {
            if (task == null)
                throw new ArgumentNullException("task");

            _task = task;
        }

        private Task _task;

        public Task Task
        {
            get { return _task; }
        }

        private Rectangle _windowBounds;

        public Rectangle WindowBounds
        {
            get { return _windowBounds; }
            set { _windowBounds = value; }
        }

        private bool _pinning;

        public bool Pinning
        {
            get { return _pinning; }
            set { _pinning = value; }
        }

        internal static StickyNote Deserialize(XElement elt, UserContext ctx)
        {
            string value;
            Task task;

            value = elt.GetAttributeString("taskId");
            try
            {
                Guid id = new Guid(value);
                task = ctx.GetTask(id);
            }
            catch
            {
                task = null;
            }

            if (task != null)
            {
                StickyNote note = new StickyNote(task);

                value = elt.GetAttributeString("windowBounds");
                if (!string.IsNullOrEmpty(value))
                {
                    TypeConverter converter = TypeDescriptor.GetConverter(typeof(Rectangle));
                    Rectangle rect = (Rectangle)converter.ConvertFromInvariantString(value);
                    note._windowBounds = rect;
                }

                note.Pinning = elt.GetAttributeBoolean("pinning") ?? false;
                note.Overflow = elt.GetAttributeBoolean("overflow") ?? false;

                return note;
            }
            else
                return null;
        }

        internal static void Serialize(XElement elt, StickyNote note)
        {
            elt.Add(
                new XAttribute("taskId", note._task.Id.ToString("N")),
                new XAttribute("windowBounds", note._windowBounds.ToShortString()));

            if (note._pinning)
                elt.Add(new XAttribute("pinning", "true"));

            if (note._overflow)
                elt.Add(new XAttribute("overflow", "true"));
        }

        private bool _overflow;

        public bool Overflow
        {
            get { return _overflow; }
            set { _overflow = value; }
        }
    }
}
