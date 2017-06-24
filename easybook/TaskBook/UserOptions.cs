using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml.Linq;
using System.ComponentModel;
using System.Reflection;
using System.Diagnostics;
using TaskBook.UI;

namespace TaskBook
{
    public class UserOptions
    {
        public UserOptions()
        {
            _stickyNoteFormSize = new Size(180, 170);
        }

        private Size _stickyNoteFormSize;
        [Option, DefaultValue(typeof(Size), "180,170")]
        public Size StickyNoteFormSize
        {
            get { return _stickyNoteFormSize; }
            set { _stickyNoteFormSize = value; }
        }

        private Dictionary<TaskImportance, ImportanceTheme> _importanceThemes;

        [Option(Storage = "_importanceThemes", Name = "Themes"), TypeConverter(typeof(ThemesDictionaryConveter))]
        public Dictionary<TaskImportance, ImportanceTheme> ImportanceThemes
        {
            get
            {
                Debug.Assert(_importanceThemes != null);
                return _importanceThemes;
            }
        }


        public readonly static Dictionary<TaskImportance, ImportanceTheme> DefaultImportanceThemes;

        static UserOptions()
        {
            DefaultImportanceThemes = new Dictionary<TaskImportance, ImportanceTheme>();

            DefaultImportanceThemes.Add(TaskImportance.Memo, new ImportanceTheme { BackColor = Color.FromArgb(200, 255, 200) });
            DefaultImportanceThemes.Add(TaskImportance.Normal, new ImportanceTheme { BackColor = Color.LightYellow });
            DefaultImportanceThemes.Add(TaskImportance.Important, new ImportanceTheme { BackColor = Color.LightSkyBlue });
            DefaultImportanceThemes.Add(TaskImportance.Extremely, new ImportanceTheme { BackColor = Color.Pink });

            foreach (var theme in DefaultImportanceThemes.Values)
            {
                Color cl = theme.BackColor;
                theme.CaptionBackColor = Color.FromArgb(
                    Math.Max(0, cl.R - 5),
                    Math.Max(0, cl.G - 5),
                    Math.Max(0, cl.B - 5));
            }

            DefaultHotKeys = new Dictionary<HotKeyType, HotKey>();

            DefaultHotKeys.Add(HotKeyType.ShowAllStickyNotes, new HotKey(0x0318004E));      // Win + N
            DefaultHotKeys.Add(HotKeyType.AddNewStickyNote, new HotKey(0x031A004E));        // Win + Ctrl + N
        }

        public ImportanceTheme GetImportanceTheme(TaskImportance importance)
        {
            ImportanceTheme theme;

            if (_importanceThemes == null)
                _importanceThemes = new Dictionary<TaskImportance, ImportanceTheme>();

            if (!_importanceThemes.TryGetValue(importance, out theme))
            {
                theme = DefaultImportanceThemes[importance].Clone();
                _importanceThemes.Add(importance, theme);
            }

            return theme;
        }

        private Dictionary<HotKeyType, HotKey> _hotKeys;
        [Option(Storage = "_hotKeys"), TypeConverter(typeof(HotKeySettingConverter))]
        public Dictionary<HotKeyType, HotKey> HotKeys
        {
            get
            {
                if (_hotKeys == null)
                    _hotKeys = new Dictionary<HotKeyType, HotKey>();
                return _hotKeys;
            }
        }

        public HotKey GetHotKey(HotKeyType type)
        {
            HotKey hk;

            if (_hotKeys == null)
                _hotKeys = new Dictionary<HotKeyType, HotKey>();

            if (_hotKeys.TryGetValue(type, out hk))
                return hk;

            hk = DefaultHotKeys[type];
            return hk;
        }

        public static readonly Dictionary<HotKeyType, HotKey> DefaultHotKeys;

        private class HotKeySettingConverter : TypeConverter
        {
            public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
            {
                if (sourceType == typeof(XElement))
                    return true;

                return base.CanConvertFrom(context, sourceType);
            }

            public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
            {
                if (destinationType == typeof(XElement))
                    return true;
                return base.CanConvertTo(context, destinationType);
            }

            public override object ConvertFrom(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value)
            {
                if (value != null && value.GetType() == typeof(XElement))
                {
                    Dictionary<HotKeyType, HotKey> dict = new Dictionary<HotKeyType, HotKey>();
                    foreach (XElement elt in ((XElement)value).Elements("Key"))
                    {
                        int id = elt.GetAttributeInt32("Type") ?? 0;
                        if (Enum.IsDefined(typeof(HotKeyType), id))
                        {
                            int data = elt.GetAttributeInt32("Keys") ?? 0;
                            dict.Add((HotKeyType)id, new HotKey(data));
                        }
                    }

                    return dict;
                }
                return base.ConvertFrom(context, culture, value);
            }

            public override object ConvertTo(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value, Type destinationType)
            {
                var dict = value as Dictionary<HotKeyType, HotKey>;
                if (destinationType == typeof(XElement) && dict != null)
                {
                    XElement parent = new XElement(((ConvertingContext)context).ElementName);
                    foreach (var entry in dict)
                    {
                        if (!entry.Value.Equals(DefaultHotKeys[entry.Key]))
                        {
                            parent.Add(new XElement("Key",
                                new XAttribute("Type", (int)entry.Key),
                                new XAttribute("Keys", entry.Value.ToInt32())
                                ));
                        }
                    }
                    return parent;
                }
                return base.ConvertTo(context, culture, value, destinationType);
            }
        }

        public class ImportanceTheme : ICloneable
        {
            public ImportanceTheme()
            {

            }

            private Color _captionBackColor;

            public Color CaptionBackColor
            {
                get { return _captionBackColor; }
                set { _captionBackColor = value; }
            }

            private Color _backColor;

            public Color BackColor
            {
                get { return _backColor; }
                set { _backColor = value; }
            }

            object ICloneable.Clone()
            {
                return this.Clone();
            }

            public ImportanceTheme Clone()
            {
                ImportanceTheme obj = new ImportanceTheme();
                obj._captionBackColor = this._captionBackColor;
                obj._backColor = this._backColor;

                return obj;
            }

            // override object.Equals
            public override bool Equals(object obj)
            {
                ImportanceTheme other = obj as ImportanceTheme;
                if (other == null) return false;

                return
                    other._captionBackColor == this._captionBackColor &&
                    other._backColor == this._backColor;
            }

            // override object.GetHashCode
            public override int GetHashCode()
            {
                return _backColor.GetHashCode() ^ _captionBackColor.GetHashCode();
            }
        }

        private bool _autoCollapse = true;
        [Option, DefaultValue(true)]
        public bool AutoCollapse
        {
            get { return _autoCollapse; }
            set { _autoCollapse = value; }
        }

        private byte _collapsedOpacity = 204;
        [Option, DefaultValue((byte)204)]
        public byte CollapsedOpacity
        {
            get { return _collapsedOpacity; }
            set { _collapsedOpacity = value; }
        }


        private bool _autoExpand = false;
        [Option, DefaultValue(false)]
        public bool AutoExpand
        {
            get { return _autoExpand; }
            set { _autoExpand = value; }
        }

        //private string _fontString;

        //[Option(Storage = "_fontString")]
        //public string FontString
        //{
        //    get { return _fontString; }
        //}

        private Font _defaultFont;
        private static readonly string[] PreferredFonts = new string[] { "微软雅黑" };
        [Option]
        public Font DefaultFont
        {
            get
            {
                if (_defaultFont == null)
                {
                    Font font;
                    FontFamily ff = null;
                    var families = FontFamily.Families;

                    foreach (var name in PreferredFonts)
                    {
                        ff = families.FirstOrDefault(o => o.Name == name);
                        if (ff != null) break;
                    }

                    if (ff == null) ff = SystemFonts.DefaultFont.FontFamily;

                    font = new Font(ff, 12);
                    _defaultFont = font;
                }
                return _defaultFont;
            }
            set
            {
                if (value == null)
                    throw new ArgumentNullException("DefaultFont");

                _defaultFont = value;
            }
        }

        internal static void Serialize(XElement elt, UserOptions obj)
        {
            var coll = TypeDescriptor.GetProperties(obj);

            foreach (PropertyDescriptor pd in coll)
            {
                OptionAttribute oa = (OptionAttribute)pd.Attributes[typeof(OptionAttribute)];

                if (oa != null)
                {
                    string name = oa.Name;
                    if (string.IsNullOrEmpty(name)) name = pd.Name;

                    object value = pd.GetValue(obj);

                    if (value != null)
                    {
                        DefaultValueAttribute dfa = (DefaultValueAttribute)pd.Attributes[typeof(DefaultValueAttribute)];
                        if (dfa == null || !object.Equals(dfa.Value, value))
                        {
                            TypeConverter converter = pd.Converter;
                            
                            if (converter != null)
                            {
                                ConvertingContext ctx = new ConvertingContext(obj, pd, name);
                                if (converter.CanConvertTo(typeof(XElement)))
                                    elt.Add((XElement)converter.ConvertTo(ctx, null, value, typeof(XElement)));
                                else
                                    elt.Add(new XElement(name, converter.ConvertToInvariantString(ctx, value)));
                            }
                            else
                                elt.Add(new XElement(name, value.ToString()));
                        }
                    }
                }
            }
        }

        internal static UserOptions Deserialize(XElement elt)
        {
            UserOptions obj = new UserOptions();

            if (elt != null)
            {
                var coll = TypeDescriptor.GetProperties(typeof(UserOptions));

                foreach (PropertyDescriptor pd in coll)
                {
                    OptionAttribute oa = (OptionAttribute)pd.Attributes[typeof(OptionAttribute)];

                    if (oa != null)
                    {
                        string name = oa.Name;
                        if (string.IsNullOrEmpty(name)) name = pd.Name;

                        var child = elt.Element(name);
                        if (child != null)
                        {

                            TypeConverter converter = pd.Converter;
                            object value;

                            if (pd.PropertyType != typeof(string))
                            {
                                if (converter != null)
                                {
                                    ConvertingContext ctx = new ConvertingContext(obj, pd, name);
                                    if (converter.CanConvertFrom(typeof(XElement)))
                                        value = converter.ConvertFrom(ctx, null, child);
                                    else
                                        value = converter.ConvertFromInvariantString(ctx, child.Value);
                                }
                                else
                                {
                                    throw new InvalidOperationException("Cannot convert from string to " + pd.PropertyType.FullName);
                                }
                            }
                            else
                                value = child.Value;


                            if (value != null)
                            {
                                name = oa.Storage;
                                if (!string.IsNullOrEmpty(name))
                                {
                                    FieldInfo field = obj.GetType().GetField(name, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
                                    if (field != null)
                                        field.SetValue(obj, value);
                                    else
                                        throw new InvalidOperationException("The storage field " + name + " not found.");
                                }
                                else
                                    pd.SetValue(obj, value);
                            }
                        }
                    }
                }
            }

            return obj;
        }

        private class ConvertingContext : ITypeDescriptorContext
        {
            object _instance;
            PropertyDescriptor _property;
            string _elementName;

            public ConvertingContext(object inst, PropertyDescriptor property, string eltname)
            {
                _instance = inst;
                _property = property;
                _elementName = eltname;
            }

            public string ElementName
            {
                get { return _elementName; }
            }

            public IContainer Container
            {
                get { return null; }
            }

            public object Instance
            {
                get { return _instance; }
            }

            public void OnComponentChanged()
            {
                
            }

            public bool OnComponentChanging()
            {
                return false;
            }

            public PropertyDescriptor PropertyDescriptor
            {
                get { return _property; }
            }

            public object GetService(Type serviceType)
            {
                return null;
            }
        }

        private class ThemesDictionaryConveter : TypeConverter
        {
            public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
            {
                if (destinationType == typeof(XElement)) return true;
                return base.CanConvertTo(context, destinationType);
            }

            public override object ConvertTo(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value, Type destinationType)
            {
                if (destinationType == typeof(XElement))
                {
                    ConvertingContext ctx = (ConvertingContext)context;
                    XElement elt = new XElement(ctx.ElementName);

                    Dictionary<TaskImportance, ImportanceTheme> dict = (Dictionary<TaskImportance, ImportanceTheme>)value;
                    TypeConverter cc = TypeDescriptor.GetConverter(typeof(Color));

                    foreach (var entry in dict)
                    {
                        var def = DefaultImportanceThemes[entry.Key];

                        if (!def.Equals(entry.Value))
                        {
                            elt.Add(new XElement(entry.Key.ToString(),
                                new XAttribute("BackColor", cc.ConvertToInvariantString(entry.Value.BackColor)),
                                new XAttribute("CaptionColor",cc.ConvertToInvariantString(entry.Value.CaptionBackColor))
                                ));
                        }
                    }

                    return elt;
                }
                else
                    return base.ConvertTo(context, culture, value, destinationType);
            }

            public override bool CanConvertFrom(ITypeDescriptorContext context, Type sourceType)
            {
                if (sourceType == typeof(XElement)) return true;
                return base.CanConvertFrom(context, sourceType);
            }

            public override object ConvertFrom(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value)
            {
                if (value != null && value is XElement)
                {
                    Dictionary<TaskImportance, ImportanceTheme> dict = new Dictionary<TaskImportance, ImportanceTheme>();
                    TypeConverter cc = TypeDescriptor.GetConverter(typeof(Color));

                    foreach (var elt in ((XElement)value).Elements())
                    {
                        string name = elt.Name.LocalName;
                        if (Enum.IsDefined(typeof(TaskImportance), name))
                        {
                            TaskImportance ti = (TaskImportance)Enum.Parse(typeof(TaskImportance), name);
                            ImportanceTheme theme = new ImportanceTheme();

                            theme.BackColor = (Color)cc.ConvertFromInvariantString(elt.GetAttributeString("BackColor"));
                            theme.CaptionBackColor = (Color)cc.ConvertFromInvariantString(elt.GetAttributeString("CaptionColor"));

                            dict.Add(ti, theme);
                        }
                    }

                    return dict;
                }
                else
                    return base.ConvertFrom(context, culture, value);
            }
        }
    }

    [AttributeUsage(AttributeTargets.Property)]
    public class OptionAttribute : Attribute
    {
        public OptionAttribute()
        {

        }

        private string _name;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        private string _storage;

        public string Storage
        {
            get { return _storage; }
            set { _storage = value; }
        }
    }


}
