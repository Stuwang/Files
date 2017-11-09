using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Test {
    class ThreadLocalTest {
        private ThreadLocal<int> _bagLocal = new ThreadLocal<int>(() => 1, true);
    }
}
