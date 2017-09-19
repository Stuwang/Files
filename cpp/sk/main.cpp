#include <iostream>
#include <functional>

#include "Function.h"

using namespace sk;

void TestStdLibExtras() {
}

int main(int argc, char const *argv[])
{
	Function<void(int n)> f = [&](int i) {
		std::cout << i << std::endl;
	};
	f(1);

	Function<void()> f2 = &TestStdLibExtras;
	f2();

	Function<void()> f3 = std::bind([](int i) {
		std::cout << "lambda " << i << std::endl;
	}, 1);
	f3();
	
	Function<void()> a = std::move(f3);
	a();
	
	return 0;
}
