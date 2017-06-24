using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TaskBook.UI
{
    public partial class RemindingTimeForm : Form
    {
        public RemindingTimeForm()
        {
            InitializeComponent();
            
        }

        public DateTime Value
        {
            get { return dateTimePicker1.Value; }
            set { dateTimePicker1.Value = value; }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Value < DateTime.Now.AddMinutes(5))
            {
                MessageBox.Show(this, "设置的提醒时间太小！", ProductName, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            else
            {
                this.DialogResult = System.Windows.Forms.DialogResult.OK;
                this.Close();
            }
        }
    }
}
