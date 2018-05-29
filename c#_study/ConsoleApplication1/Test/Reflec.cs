using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace Test {

    public sealed class TestAttribute : System.Attribute {
        public string[] info { set; get; }
        public TestAttribute(string[] data) {
            info = data;
        }
    }

    [TestAttribute(new string[]{"hahahhahha","adasdasdas"})]
    public class Reflec  {
        int id;
        string name;
        public static void Test() {
            Type t = Type.GetType("Test.Reflec");
            //if (t != null) { 
            //    Console.WriteLine(t.Name);
            //    Console.WriteLine(t.StructLayoutAttribute);
            //}

            (from n in t.GetMethods() select n.Name).ToList().ForEach(_=>Console.WriteLine(_));

            Reflec _1 = new Reflec();
            var arr = typeof(Reflec).GetCustomAttribute<TestAttribute>();
            arr.info.ToList().ForEach(Console.WriteLine);

            new object();
            new Object();
        }
    }
}
