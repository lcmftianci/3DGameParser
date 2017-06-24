using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Globalization;

namespace TaskBook.Localization
{
    public class LocaleInfo
    {
        private LocaleInfo()
        {
        }

        private int _lcid;

        public int Lcid
        {
            get { return _lcid; }
        }

        private Glossary _glossary;

        public Glossary Glossary
        {
            get { return _glossary ?? _default._glossary; }
        }

        private string _name;

        public string Name
        {
            get { return _name; }
        }

        private string _displayName;

        public string DisplayName
        {
            get { return _displayName; }
        }


        static LocaleInfo _current;
        static LocaleInfo _default;

        public static LocaleInfo Current
        {
            get
            {
                if (_current == null)
                {
                    CultureInfo culture = CultureInfo.CurrentUICulture;
                    if (culture.LCID == Default.Lcid)
                        _current = _default;
                    else
                        _current = GetLocale(culture);
                }

                return _current;
            }
        }

        public static LocaleInfo Default
        {
            get
            {
                if (_default == null)
                    _default = GetLocale(CultureInfo.GetCultureInfo("en-US"));
                return _default;
            }
        }

        public string Translate(string id)
        {
            return Translate(id, null);
        }

        public string Translate(string id, params object[] args)
        {
            string format = GetText(id);

            if (format != null)
            {
                if (args != null && args.Length > 0)
                    return string.Format(format, args);
                else
                    return format;
            }
            else
                return id;
        }

        public string GetText(string id)
        {
            Glossary gl = this.Glossary;
            string format = null;

            if (gl.IsDefined(id))
            {
                format = gl[id];
            }
            else if (gl != _default._glossary)
            {
                gl = _default._glossary;
                if (gl.IsDefined(id))
                    format = gl[id];
            }

            return format;
        }

        public string TranslateEnum(object value)
        {
            if (value == null) return "";

            string id = "enum." + value.GetType().Name + "." + value;
            string text = Translate(id);
            if (id != text)
                return text;
            else
                return value.ToString();
        }

        public static LocaleInfo GetLocale(CultureInfo culture)
        {
            LocaleInfo info = new LocaleInfo();

            info._lcid = culture.LCID;
            info._glossary = Glossary.GetGlossary(culture);
            info._name = culture.Name;
            info._displayName = culture.DisplayName;

            return info;
        }

        public string ProductName
        {
            get { return Translate("app.product_name"); }
        }
    }
}
