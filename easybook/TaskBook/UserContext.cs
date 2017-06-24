using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Diagnostics;

namespace TaskBook
{
    public class UserContext
    {
        string _dataFilePath;

        private UserContext()
        {
            _notes = new Dictionary<Guid, StickyNote>();
            _tasks = new List<Task>();
            _categories = new List<string>();
        }

        List<Task> _tasks;
        List<string> _categories;
        Dictionary<Guid, StickyNote> _notes;
        //LocalStorage _storage;

        public Task[] GetTasks()
        {
            return _tasks.OrderByDescending(o => o.CreationTime).ToArray();
        }

        private UserOptions _options;

        public UserOptions Options
        {
            get { return _options; }
        }


        public Task GetTask(Guid id)
        {
            Task task = _tasks.SingleOrDefault(o => o.Id == id);
            if (task == null)
                throw new ArgumentException("Invalid task ID: " + id);

            return task;
        }

        public void AddTask(Task task)
        {
            AddTask(task, true);
        }

        private void AddTask(Task task, bool raiseEvent)
        {
            if (task == null)
                throw new ArgumentNullException("task");


            _tasks.Add(task);

            string category = task.Category;

            if (!string.IsNullOrEmpty(category) && !_categories.Contains(category, StringComparer.InvariantCultureIgnoreCase))
                _categories.Add(category);

            if (raiseEvent && TaskAdded != null)
            {
                TaskAdded(this, new TaskEventArgs(task));
            }
        }

        public void AddStickyNote(StickyNote note)
        {
            if (note == null)
                throw new ArgumentNullException("note");

            Guid id = note.Task.Id;
            if (_notes.ContainsKey(id))
                throw new ArgumentException("ID already exists: " + id);

            _notes.Add(id, note);
        }

        public ICollection<StickyNote> StickyNotes
        {
            get
            {
                return _notes.Values;
            }
        }

        public string[] Categories
        {
            get
            {
                return _categories.ToArray();
            }
        }

        public static UserContext Load(string path)
        {
            UserContext uc = new UserContext();
            uc._dataFilePath = path;

            if (System.IO.File.Exists(path))
            {
                XDocument doc = XDocument.Load(path);

                XElement root = doc.Element("taskBook");

                uc._options = UserOptions.Deserialize(root.Element("options"));

                foreach (var elt in root.Element("tasks").Elements("task"))
                {
                    Task task = Task.Deserialize(elt);
                    uc.AddTask(task, false);
                }

                foreach (var elt in root.Element("stickyNotes").Elements("note"))
                {
                    StickyNote note = StickyNote.Deserialize(elt, uc);
                    if (note != null)
                        uc.AddStickyNote(note);
                }
            }
            else
            {
                var task = Task.New("从这里开始你的任务！", null);
                task.Importance = TaskImportance.Normal;
                uc.AddTask(task);
                uc.AddStickyNote(new StickyNote(task));

                uc._options = new UserOptions();
            }

            return uc;
        }

        public event EventHandler<TaskEventArgs> TaskDeleted;
        public event EventHandler<TaskEventArgs> TaskAdded;

        public void DeleteTask(Task task)
        {
            if (task == null)
                throw new ArgumentNullException("task");

            int index;

            index = _tasks.IndexOf(task);
            if (index >= 0)
            {
                _tasks.RemoveAt(index);

                if (_notes.ContainsKey(task.Id))
                    _notes.Remove(task.Id);

                Persist();

                if (TaskDeleted != null)
                    TaskDeleted(this, new TaskEventArgs(task));
            }
            else
                throw new ArgumentException("Task not registered.");
        }

        public void Persist()
        {
            var doc = new XDocument(
                new XElement("taskBook",
                    new XElement("versions",
                        new XAttribute("file", "1.0"),
                        new XAttribute("app", "1.0")
                        )));

            XElement parent, elt;

            doc.Root.Add(parent = new XElement("options"));
            UserOptions.Serialize(parent, _options);

            doc.Root.Add(parent = new XElement("tasks"));

            foreach (var task in _tasks)
            {
                elt = new XElement("task");
                parent.Add(elt);
                Task.Serialize(elt, task);
            }

            doc.Root.Add(parent = new XElement("stickyNotes"));
            foreach (var note in _notes.Values)
            {
                parent.Add(elt = new XElement("note"));
                StickyNote.Serialize(elt, note);
            }

            doc.Save(_dataFilePath);
        }

        internal void DeleteStickyNote(Guid id)
        {
            StickyNote note;

            if (_notes.TryGetValue(id, out note))
            {
                _notes.Remove(id);
            }
        }
    }
}
