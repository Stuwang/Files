using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace WpfApplication1
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        void init()
        {
            this.Exit += delegate(object sender,ExitEventArgs e) {

            };
            this.Exit += this.App_Exit;
        }

        private void App_Exit(object sender, ExitEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}
