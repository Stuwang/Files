using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class InAndPut {
    public class Struct {
        public int value { set; get; }
        public void Print(string s = "") {
            Console.Write(s);
            Console.Write("the value is ");
            Console.WriteLine(value);
        }
    }

    public static void TestIn(Struct s) {
        //s.value = 1;
        s.Print();
    }

    public static void TestOut(out Struct s) {
        s = new Struct();
        s.value = 11;
        s.Print();
    }


    public static void test() {
        {
            Struct s = new Struct();
            s.value = 12;
            TestIn(s);
        }
        //{
        //    Struct s;
        //    TestOut(out s);
        //    s.Print();
        //}
        {
            Struct s = new Struct();
            s.value = 12;
            s.Print("test function");
            TestRef(ref s);
            s.Print("test function");
        }

    }

    private static void TestRef(ref Struct s) {
        s.Print("TestRef");
        s.value = 11;
        s.Print("TestRef");
    }
}

