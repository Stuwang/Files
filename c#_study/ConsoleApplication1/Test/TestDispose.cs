using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test {
    public class TestDispose : IDisposable {

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        void Dispose(bool disposing) {
            if (!m_disposed) {
                if (disposing) {
                    Console.WriteLine("Dispose bool");
                }
                m_disposed = true;
            }
        }

        ~TestDispose() {
            Dispose(false);
            Console.WriteLine("~TestDispose");
        }

        private bool m_disposed;

        public static void Test() {
            TestDispose t = null;
            using (t = new TestDispose()) {
                Console.WriteLine("ahhahaha");
            }
        }

    }
}
