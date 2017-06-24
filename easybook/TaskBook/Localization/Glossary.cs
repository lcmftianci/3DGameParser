using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;
using System.IO;
using System.Xml.Linq;
using System.ComponentModel;

namespace TaskBook.Localization
{
    public class Glossary : ICustomTypeDescriptor
    {
        Dictionary<string, Entry> _entries;

        private Glossary()
        {
            _entries = new Dictionary<string, Entry>(StringComparer.InvariantCultureIgnoreCase);
        }

        private string _language;

        public string Language
        {
            get { return _language; }
            private set
            {
                if (value == null)
                    throw new ArgumentNullException();

                int lcid;
                CultureInfo culture;

                try
                {
                    if (int.TryParse(value, out lcid))
                    {
                        culture = CultureInfo.GetCultureInfo(lcid);
                    }
                    else
                    {
                        culture = CultureInfo.GetCultureInfo(value);
                    }
                }
                catch(Exception x)
                {
                    throw new ArgumentException("Not a valid lang string.", x);
                }


                _lcid = culture.LCID;
                _language = culture.Name;
            }
        }

        private int _lcid;

        public int Lcid
        {
            get { return _lcid; }
        }

        private void Merge(Glossary other)
        {
            if (other != null && this != other && _lcid == other._lcid)
            {
                Entry entry0, entry1;
                foreach (var pair in other._entries)
                {
                    if (_entries.TryGetValue(pair.Key, out entry0))
                    {
                        entry1 = pair.Value;
                        if (!string.IsNullOrEmpty(entry1.Content))
                            entry0.Content = entry1.Content;
                    }
                    else
                        _entries.Add(pair.Key, pair.Value);
                }
            }
        }

        public string[] GetEntryIds(string startsWith)
        {
            IEnumerable<String> q = _entries.Keys;
            if (!string.IsNullOrEmpty(startsWith))
                q = q.Where(o => o.StartsWith(startsWith, StringComparison.InvariantCultureIgnoreCase));
            return q.OrderBy(o => o).ToArray();
        }

        public bool IsDefined(string id)
        {
            return _entries.ContainsKey(id);
        }

        public string this[string id]
        {
            get
            {
                Entry entry;

                if (_entries.TryGetValue(id, out entry))
                    return entry.Content;
                else
                    return null;
            }
        }

        internal static Glossary GetGlossary(CultureInfo culture)
        {
            Glossary gl;

            if (_glossaries == null)
            {
                _glossaries = new Dictionary<int, Glossary>();
                using (StringReader reader = new StringReader(Properties.Resources.DefaultGlossary))
                {
                    gl = LoadGlossary(reader);
                    _glossaries.Add(gl.Lcid, gl);
                }
                InitializeGlossaries();
            }

            if (_glossaries.TryGetValue(culture.LCID, out gl))
                return gl;
            else
                return null;
        }

        private static void InitializeGlossaries()
        {
            Uri uri = new Uri(typeof(Glossary).Assembly.CodeBase);
            string path = Path.GetDirectoryName(uri.LocalPath);
            Glossary gl, gl0;

            foreach (string filename in Directory.GetFiles(path, "*.glr"))
            {
                using (StreamReader reader = new StreamReader(filename))
                {
                    try
                    {
                        gl = LoadGlossary(reader);
                    }
                    catch
                    {
                        gl = null;
                    }
                }

                if (gl != null)
                {
                    if (_glossaries.TryGetValue(gl.Lcid, out gl0))
                        gl0.Merge(gl);
                    else
                        _glossaries.Add(gl.Lcid, gl);
                }
            }
        }

        static Dictionary<int, Glossary> _glossaries;

        private static Glossary LoadGlossary(TextReader reader)
        {

            XDocument doc = XDocument.Load(reader);

            Glossary gl;

            try
            {
                gl = new Glossary();
                gl.Language = doc.Root.Attribute("lang").Value;

                foreach (XElement elt in doc.Root.Elements("entry"))
                {
                    Entry entry = new Entry(elt);
                    gl._entries.Add(entry.Id, entry);
                }
            }
            catch (ArgumentException)
            {
                gl = null;
            }

            return gl;
        }

        class Entry
        {
            public Entry(XElement elt)
            {
                _id = elt.Attribute("id").Value;
                _content = elt.Value;
            }

            private string _id;

            public string Id
            {
                get { return _id; }
            }

            private string _content;

            public string Content
            {
                get { return _content; }
                set { _content = value; }
            }

        }


        AttributeCollection ICustomTypeDescriptor.GetAttributes()
        {
            return null;
        }

        string ICustomTypeDescriptor.GetClassName()
        {
            return typeof(Glossary).Name;
        }

        string ICustomTypeDescriptor.GetComponentName()
        {
            return ((ICustomTypeDescriptor)this).GetClassName();
        }

        TypeConverter ICustomTypeDescriptor.GetConverter()
        {
            return null;
        }

        EventDescriptor ICustomTypeDescriptor.GetDefaultEvent()
        {
            return null;
        }

        PropertyDescriptor ICustomTypeDescriptor.GetDefaultProperty()
        {
            return null;
        }

        object ICustomTypeDescriptor.GetEditor(Type editorBaseType)
        {
            return null;
        }

        EventDescriptorCollection ICustomTypeDescriptor.GetEvents(Attribute[] attributes)
        {
            return null;
        }

        EventDescriptorCollection ICustomTypeDescriptor.GetEvents()
        {
            return null;
        }

        PropertyDescriptorCollection ICustomTypeDescriptor.GetProperties(Attribute[] attributes)
        {
            List<PropertyDescriptor> list = new List<PropertyDescriptor>();

            string startsWith = null;
            if (attributes != null)
            {
                DisplayNameAttribute attr = attributes.OfType<DisplayNameAttribute>().FirstOrDefault();
                if (attr != null)
                    startsWith = attr.DisplayName;
            }

            foreach (string id in GetEntryIds(startsWith))
            {
                PropertyDescriptor prop = new EntryProperty(id);
                list.Add(prop);
            }

            return new PropertyDescriptorCollection(list.ToArray(), true);
        }

        PropertyDescriptorCollection ICustomTypeDescriptor.GetProperties()
        {
            return ((ICustomTypeDescriptor)this).GetProperties(null);
        }

        object ICustomTypeDescriptor.GetPropertyOwner(PropertyDescriptor pd)
        {
            return this;
        }

        class EntryProperty : PropertyDescriptor
        {
            string _entryId;

            public EntryProperty(string entryId)
                : base(entryId.Replace('.', '$'), new Attribute[] { ReadOnlyAttribute.Yes})
            {
                _entryId = entryId;
            }

            public override string DisplayName
            {
                get
                {
                    return _entryId;
                }
            }

            public override bool CanResetValue(object component)
            {
                return false;
            }

            public override Type ComponentType
            {
                get { return typeof(Glossary); }
            }

            public override object GetValue(object component)
            {
                Glossary obj = component as Glossary;
                if (obj == null)
                    throw new ArgumentException();
                if (obj.IsDefined(_entryId))
                    return obj[_entryId];

                obj = LocaleInfo.Default.Glossary;
                if (obj.IsDefined(_entryId))
                    return obj[_entryId];
                else
                    return _entryId;
            }

            public override bool IsReadOnly
            {
                get { return true; }
            }

            public override Type PropertyType
            {
                get { return typeof(string); }
            }

            public override void ResetValue(object component)
            {
                throw new InvalidOperationException();
            }

            public override void SetValue(object component, object value)
            {
                throw new InvalidOperationException();
            }

            public override bool ShouldSerializeValue(object component)
            {
                return false;
            }
        }

    }
}
