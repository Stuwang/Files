using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    class InterfaceCallBack {

        interface Callback{
            void call(int i);
        }

        class Executer {
            public static void Run(int value, Callback cb) {
                if (null != cb) {
                    cb.call(value);
                }else{
                    Console.WriteLine("null input");
                }
            }

        }

        class TestCall : Callback {
            public void call(int i) {
                Console.WriteLine("called   " + i);
            }
        }

        public static void test() {
            Executer.Run(1, null);
            Executer.Run(1,new TestCall());
        }
    }
}
