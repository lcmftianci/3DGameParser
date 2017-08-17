using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Drawing;
using System.IO;


namespace EmbededHtml5
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Bitmap srcBitmap = null;//用于保存原图
        System.Drawing.Size size;//用于保存目标图标的大小
      /*  public MainWindow()
        {
            InitializeComponent();
            string szTmp = "http://www.baidu.com";
            Uri uri = new Uri(szTmp);
            webbrowser1.Navigate(uri);
        }

        <WebBrowser x:Name="webbrowser1" HorizontalAlignment="Left" Height="293" VerticalAlignment="Top" Width="517" LoadCompleted="web_Loaded"
                    IsEnabled="False"/>
        <Button x:Name="button" Content="Button" HorizontalAlignment="Left" Margin="223,298,0,0" VerticalAlignment="Top" Width="75" Click="button_Click"/>

        private void button_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.MessageBox.Show("日历");
        }

        private void web_Loaded(object sender, NavigationEventArgs e)
        {
            // ((sender as WebBrowser).Document as mshtml.HTMLDocumentEvents_Event).oncontextmenu += new mshtml.
            ((sender as System.Windows.Controls.WebBrowser).Document as mshtml.HTMLDocumentEvents_Event).oncontextmenu += new mshtml.HTMLDocumentEvents_oncontextmenuEventHandler(ExtendFrameControl_oncontextmenu);
            mshtml.HTMLDocument dom = (mshtml.HTMLDocument)webbrowser1.Document; //定义HTML
            dom.documentElement.style.overflow = "hidden"; //隐藏浏览器的滚动条
            dom.body.setAttribute("scroll", "no"); //禁用浏览器的滚动条
            if (!dom.body.innerHTML.Contains("123456"))
            {
                string szTmp = "http://www.baidu.com";
                Uri uri = new Uri(szTmp);
                webbrowser1.Navigate(uri);
            }
        }
        bool ExtendFrameControl_oncontextmenu()
        {
            return false;
        }
        */
        private void cmbSize_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cmbSize.SelectedIndex == 0)
                size = new System.Drawing.Size(16, 16);
            else if (cmbSize.SelectedIndex == 1)
                size = new System.Drawing.Size(32, 32);
            else if (cmbSize.SelectedIndex == 2)
                size = new System.Drawing.Size(64, 64);
        }

        private void btnOk_Click(object sender, RoutedEventArgs e)
        {
            //弹出对话框
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.InitialDirectory = "F:\\";
            dlg.Filter = "图片(*.jpg,*.png,*.bmp)|*.jpg;*.png;*.bmp";
            dlg.ValidateNames = true;
            dlg.CheckFileExists = true;
            dlg.CheckPathExists = true;
            //Nullable<bool> result = dlg.ShowDialog();
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtImage.Text = dlg.FileName;
                srcBitmap = new Bitmap(dlg.FileName);
                imgJpeg.Source = new BitmapImage(new Uri(txtImage.Text, UriKind.RelativeOrAbsolute));
            }
        }

        private void btnMake_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (txtImage.Text != "" && cmbSize.Text != "")
                {
                    SaveFileDialog dlg = new SaveFileDialog();
                    dlg.Filter = "图标(*.ico)|*.ico";
                    dlg.CheckPathExists = true;
                    if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                    {
                        FileStream fs = new FileStream(dlg.FileName, FileMode.Create);
                        System.Drawing.Icon icon = ConvertBitmap2Ico(srcBitmap);
                        //将Icon保存的指定的输出
                        icon.Save(fs);
                        fs.Close();
                    }
                }
            }
            catch (Exception err)
            {
                System.Windows.MessageBox.Show(err.ToString());
            }
        }

        //bitmap转化为ico文件
        private Icon ConvertBitmap2Ico(Bitmap bitmap)
        {
            Bitmap icoBitmap = new Bitmap(bitmap, size);
            //获得原位图的图标句柄
            var a = icoBitmap.GetHicon();
            //从图标的指定WINDOWS句柄创建Icon
            System.Drawing.Icon icon = System.Drawing.Icon.FromHandle(a);
            return icon;
        }
    }
}
