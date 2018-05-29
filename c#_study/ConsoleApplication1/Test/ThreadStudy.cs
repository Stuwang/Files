using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LinqTest {
    class ThreadStudy {
        static void thread() {
            var t = new Thread(() => {
                int i = 10;
                while (0 != i--) {
                    Thread.Sleep(200);
                    Console.WriteLine("thread");
                }
            });
            t.IsBackground = true;
            t.Start();
            var tc = Thread.CurrentThread;
            if (tc == t) {
                Console.WriteLine(true);
            }
            else {
                tc.Name = "Main";
                Console.WriteLine("" + false + tc.Name);
            }
            //t.Join();
        }

        static void CurrentThread() {
            Thread thread = Thread.CurrentThread;
            thread.Name = "Main Thread";
            string threadMessage = string.Format("Thread ID:{0}\n    Current AppDomainId:{1}\n    " +
              "Current ContextId:{2}\n    Thread Name:{3}\n    " +
              "Thread State:{4}\n    Thread Priority:{5}\n",
              thread.ManagedThreadId, Thread.GetDomainID(), Thread.CurrentContext.ContextID,
              thread.Name, thread.ThreadState, thread.Priority);
            Console.WriteLine(threadMessage);
        }


        static void test_() {
            var list = new List<string> {
            "aaaa",
            "bbbbb"
        };
            list.ForEach(Console.WriteLine);
        }

        delegate void Print(string d);
        static void TestDelegate() {
            Print p = _ => Console.WriteLine(_);
            p += _ => Console.WriteLine(_ + "   asad");
            p("aaaa");
        }


        delegate void PrintType(string value);
    }
}
