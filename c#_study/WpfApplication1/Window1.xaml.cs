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
using System.Windows.Shapes;

namespace WpfApplication1
{
  /// <summary>
  /// Window1.xaml 的交互逻辑
  /// </summary>
  public partial class Window1 : Window
  {
    public Window1()
    {
      InitializeComponent();
    }

    private void b1_Click(object sender, RoutedEventArgs e)
    {
      t00.Text = "aaaa";
      t01.Text = "aaaa";
      t02.Text = "aaaa";
      t03.Text = "aaaa";
      t04.Text = "aaaa";
      t05.Text = "aaaa";

      t10.Text = "aaaa";
      t11.Text = "aaaa";
      t12.Text = "aaaa";
      t13.Text = "aaaa";
      t14.Text = "aaaa";
      t15.Text = "aaaa";

      child.Visibility =Visibility.Hidden;
      MessageBox.Show("hahah");
      child.Visibility = Visibility.Visible;
    }
  }
}
