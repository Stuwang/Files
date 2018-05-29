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
using System.Windows.Shapes;

namespace WpfStudy
{
    /// <summary>
    /// Decode.xaml 的交互逻辑
    /// </summary>
    public partial class Decode : Window
    {
        public string text_context { set; get; }

        public Decode()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            //text1.Text += "123456";
            MessageBox.Show(text1.Text);
            
        }

        private void text_TextChanged(object sender, TextChangedEventArgs e)
        {
            string text = (sender as TextBox).Text;
            text1.Text = text;
            text2.Text = text;
        }

        private void text2_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            //MessageBox.Show(e.Text);
        }
    }
}
