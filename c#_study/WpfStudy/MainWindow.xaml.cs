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

        private void Button1_Click(object sender, RoutedEventArgs e)
        {
            Decode d = new Decode();
            d.Show();
        }

        private void Button2_Click(object sender, RoutedEventArgs e)
        {
            new ScrollViewerWindow().Show();
        }

        private void Button3_Click(object sender, RoutedEventArgs e)
        {
            new WindowBindData().Show();
        }
    }
}
