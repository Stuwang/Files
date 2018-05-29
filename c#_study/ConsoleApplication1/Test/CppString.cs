using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LinqTest {
    class CppString {
        [DllImport("CppDll.dll",
            EntryPoint = "GetString", 
            CharSet = CharSet.Ansi, 
            CallingConvention = CallingConvention.Winapi)]
        public static extern IntPtr GetString();

        [DllImport("CppDll.dll",
            EntryPoint = "Print", 
            CharSet = CharSet.Ansi, 
            CallingConvention = CallingConvention.Winapi)]
        public static extern void PutString(String str);

        public static void TestPutString() {
            StringBuilder str = new StringBuilder(255); //255 是 capacity
            str.Append("aaasddddddddddddddddddddd");
            PutString("aaaaaaaa");
        }

        public static void TestGetString() {
            IntPtr intPtr = GetString();
            string str = Marshal.PtrToStringAuto(intPtr);
            Console.WriteLine(str);
        }

        public static void Test() {
            TestPutString();
        }
    }
}
