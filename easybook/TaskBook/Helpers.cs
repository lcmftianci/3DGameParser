using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Drawing;

namespace TaskBook
{
    internal static class Helpers
    {
        public static string GetAttributeString(this XElement elt, XName name)
        {
            XAttribute attr = elt.Attribute(name);

            if (attr != null) return attr.Value;
            else return null;
        }

        public static DateTime? GetAttributeDateTime(this XElement elt, XName name)
        {
            string text = GetAttributeString(elt, name);

            if (string.IsNullOrEmpty(text))
                return null;
            else
                return DateTime.Parse(text);
        }

        public static T GetAttributeEnum<T>(this XElement elt, XName name)
        {
            string value = GetAttributeString(elt, name);

            if (!string.IsNullOrEmpty(value))
            {
                return (T)Enum.Parse(typeof(T), value);
            }
            else
                return default(T);
        }

        public static bool? GetAttributeBoolean(this XElement elt, XName name)
        {
            string value = GetAttributeString(elt, name);

            if (!string.IsNullOrEmpty(value))
            {
                bool b;

                if (bool.TryParse(value, out b))
                    return b;

                value = value.ToLower();

                if (value == "yes" || value == "1") return true;
                else return false;
            }
            else
                return null;
        }

        public static int? GetAttributeInt32(this XElement elt, XName name)
        {
            string value = GetAttributeString(elt, name);

            if (!string.IsNullOrEmpty(value))
            {
                return int.Parse(value);
            }
            else
                return null;

        }

        public static string ToShortString(this Rectangle rect)
        {
            return string.Format("{0},{1},{2},{3}",
                rect.Left, rect.Top, rect.Width, rect.Height);
        }
    }
}
