using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Xml.Linq;

namespace TaskBook
{
    public class Task : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        bool _loading;

        public Task()
        {

        }

        internal void BeginLoad()
        {
            _loading = true;
        }

        internal void EndLoad()
        {
            _loading = false;
        }

        private string _content;

        public string Contents
        {
            get { return _content; }
            set
            {
                if (_content != value)
                {
                    _content = value;
                    OnPropertyChanged("Contents");
                }
            }
        }

        private string _contentRtf;

        public string ContentsRtf
        {
            get { return _contentRtf; }
            set
            {
                _contentRtf = value;
                OnPropertyChanged("ContentsRtf");
            }
        }
        

        private DateTime? _remindingTime;

        public DateTime? RemindingTime
        {
            get { return _remindingTime; }
            set
            {
                if (_remindingTime != value)
                {
                    _remindingTime = value;
                    OnPropertyChanged("RemindingTime");
                    if (!_loading && value != null && value.Value > DateTime.Now)
                        Reminded = false;
                }
            }
        }

        private bool _reminded;

        public bool Reminded
        {
            get { return _reminded; }
            set
            {
                if (_reminded != value)
                {
                    _reminded = value;
                    OnPropertyChanged("Reminded");
                }
            }
        }

        public bool NeedsRemind
        {
            get
            {
                return !_reminded && _remindingTime != null;
            }
        }

        private DateTime _creationTime;

        public DateTime CreationTime
        {
            get { return _creationTime; }
            internal set
            {
                if (!_loading)
                    throw new InvalidOperationException("This property is read-only.");
            }
        }

        private bool _finished;

        public bool Finished
        {
            get { return _finished; }
            set
            {
                if (_finished != value)
                {
                    _finished = value;
                    OnPropertyChanged("Finished");
                    if (!_loading)
                    {
                        if (_finished)
                            FinishTime = DateTime.Now;
                        else
                            FinishTime = null;
                    }
                }
            }
        }

        private DateTime? _finishTime;

        public DateTime? FinishTime
        {
            get { return _finishTime; }
            internal set
            {
                if (!_loading)
                {
                    if (_finishTime != value)
                    {
                        _finishTime = value;
                        OnPropertyChanged("FinishTime");
                    }
                }
                else
                    throw new InvalidOperationException("This property is read-only.");
            }
        }

        private Guid _id;

        public Guid Id
        {
            get { return _id; }
            internal set
            {
                if (_loading) _id = value;
                else throw new InvalidOperationException("This property is read-only.");
            }
        }

        private string _category;

        public string Category
        {
            get { return _category; }
            set
            {
                if (_category != value)
                {
                    _category = value;
                    OnPropertyChanged(new PropertyChangedEventArgs("Category"));
                }
            }
        }

        private TaskImportance _importance;

        public TaskImportance Importance
        {
            get { return _importance; }
            set
            {
                if (_importance != value)
                {
                    _importance = value;
                    OnPropertyChanged(new PropertyChangedEventArgs("Importance"));
                }
            }
        }

        public static Task New(string content, DateTime? remindingTime)
        {
            Task task = new Task();
            task.BeginLoad();
            task._id = Guid.NewGuid();
            task._creationTime = DateTime.Now;
            task._content = content;
            task.EndLoad();
            return task;
        }

        private void OnPropertyChanged(params string[] properties)
        {
            if (properties.Length > 0)
            {
                foreach (var p in properties)
                    OnPropertyChanged(new PropertyChangedEventArgs(p));
            }
        }

        protected void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            if (!_loading && this.PropertyChanged != null)
                this.PropertyChanged(this, e);
        }


        internal static Task Deserialize(XElement elt)
        {
            Task task = new Task();

            XAttribute attr;

            if ((attr = elt.Attribute("id")) != null)
                task._id = new Guid(attr.Value);
            else
                throw new ArgumentException();

            task._content = elt.Element("text").Value;

            var telt = elt.Element("rtf");
            if (telt != null)
                task._contentRtf = telt.Value;

            task._category = elt.GetAttributeString("category");
            task._importance = elt.GetAttributeEnum<TaskImportance>("importance");
            task._creationTime = elt.GetAttributeDateTime("creationTime") ?? DateTime.Now;

            task._finished = elt.GetAttributeBoolean("finished") ?? false;
            task._finishTime = elt.GetAttributeDateTime("finishTime");

            task._reminded = elt.GetAttributeBoolean("reminded") ?? false;
            task._remindingTime = elt.GetAttributeDateTime("remindingTime");


            return task;
        }

        internal static void Serialize(XElement elt, Task task)
        {
            elt.Add(
                new XAttribute("id", task.Id.ToString("N")),
                new XAttribute("creationTime", task.CreationTime.ToString("g")),
                new XAttribute("importance", (int)task.Importance)
                );

            if (task._category != null)
                elt.Add(new XAttribute("category", task._category));

            if (task._finished) 
                elt.Add(new XAttribute("finished", "true"),
                    new XAttribute("finishTime", task._finishTime.Value.ToString("g")));

            if (task.Reminded)
                elt.Add(new XAttribute("reminded", "true"));

            if (task.RemindingTime != null)
                elt.Add(new XAttribute("remindingTime", task._remindingTime.Value.ToString("g")));

            elt.Add(
                new XElement("text", task._content ?? string.Empty),
                new XElement("rtf", task._contentRtf ?? string.Empty));
        }

    }
}
