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
    /// GirdWindow.xaml 的交互逻辑
    /// </summary>
    public partial class GirdWindow : Window
    {
        public GirdWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DisableAllPage();
            g1.Visibility = Visibility.Visible;
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            DisableAllPage();
            g2.Visibility = Visibility.Visible;
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            DisableAllPage();
            g3.Visibility = Visibility.Visible;
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            DisableAllPage();
            g4.Visibility = Visibility.Visible;
        }

        void DisableAllPage()
        {
            g1.Visibility = Visibility.Hidden;
            g2.Visibility = Visibility.Hidden;
            g3.Visibility = Visibility.Hidden;
            g4.Visibility = Visibility.Hidden;
        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            dataGrid1.CanUserAddRows = true;
            var a = new List<Student>();
            Student stu;
            stu.age = 21;
            stu.name = "aaa";
            stu.sex = "aaa";

            a.Add(stu);
            a.Add(stu);
            a.Add(stu);
            a.Add(stu);
            a.Add(stu);
            a.Add(stu);

            dataGrid1.DataContext = a;
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {
            //Button b = new Button();
            //b.Name = "test";
            b3.Name = "aaaaa";
        }

        public string b3_button_s;
        //public List<Student> list_;
    }

    struct Student
    {
        public string name;
        public int age;
        public string sex;
    }
}
