using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace LinqTest {
    class MyFile {
        public static void TestFileInfo() {
            FileInfo fileinfo = new FileInfo(@"H:\workspace\c_sharp\WpfApplication1\WpfApplication1.psess");
            if (fileinfo.Exists) {
                Console.WriteLine(fileinfo.Length);
                Console.WriteLine(fileinfo.Name);
                Console.WriteLine(fileinfo.DirectoryName);
                Console.WriteLine(fileinfo.IsReadOnly);
                Console.WriteLine(fileinfo.LastAccessTime);
                Console.WriteLine(fileinfo.Exists);
            }

        }

        public static string Get<T>() where T :MyFile {
            return typeof(T).Name;
        }

        public static void Invoke() {
            //Console.WriteLine(Get<string>());
            //Console.WriteLine(Get<Object>());
            //Console.WriteLine(Get<int>());
            //Console.WriteLine(Get<bool>());
            Console.WriteLine(Get<MyFile>());
        }

        public static void Run() {
            Invoke();
        }
    }
}
