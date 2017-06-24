using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Linq.Mapping;
using System.ComponentModel;

namespace TaskBook.DataAccess
{
    [Table(Name = "UserOptions")]
    internal class UserOptionItem : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public UserOptionItem()
        {

        }

        public UserOptionItem(string key)
        {
            _key = key;
        }

        private string _key;
        [Column(Name = "Key", IsPrimaryKey = true, Storage = "_key")]
        public string Key
        {
            get { return _key; }
        }

        private string _valueText;
        [Column(Name = "ValueText", CanBeNull = true, Storage = "_valueText", UpdateCheck = UpdateCheck.Never)]
        public string ValueText
        {
            get
            {
                return _valueText;
            }
            set
            {
                if (_valueText != value)
                {
                    _valueText = value;
                    if (PropertyChanged != null)
                        PropertyChanged(this, new PropertyChangedEventArgs("ValueText"));
                }
            }
        }
    }
}
