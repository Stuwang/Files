using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfStudy
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (e.OriginalSource == button1)
            {
                if (sender == button1)
                {
                    MessageBox.Show("Yes, the sender is the same as event.OriginalSource");
                }
                //else
                //{
                //    MessageBox.Show("the sender is not the same as event.OriginalSource");
                //}
                Decode d = new Decode();
                d.Show();
            }
            else if (e.OriginalSource == button2)
            {
                new ScrollViewerWindow().Show();
            }
            else if (e.OriginalSource == button3)
            {
                new WindowBindData().Show();
            }else if(e.OriginalSource == button4)
            {
                new SliderWindow().Show();
            }
            else
            {
                MessageBox.Show("Oh,Sorry,UnKnow Button");
            }

        }

        private void Grid_KeyDown(object sender, KeyEventArgs e)
        {
            MessageBox.Show(e.Key.ToString());
        }
    }
}
