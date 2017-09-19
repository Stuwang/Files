#include <string>

#include "Concepts.h"

namespace cp {


};

template<cp::CopyAssignable T>
void f(T ) {};

struct TestClass {
	constexpr TestClass() {};
	TestClass(const TestClass&) = default;
	TestClass& operator=(const TestClass&) = default;
	TestClass(const TestClass&&) {};
	TestClass& operator=(const TestClass&&) {return *this;};
	~TestClass(){};

	friend bool operator<(const TestClass&, const TestClass&) {
		return true;
	};

	friend bool operator==(const TestClass&, const TestClass&);

	int operator()()const {};

	int operator()(int, int)const {};
};


int main() {
	TestClass t;
	std::string s = "";
	f(t);
	// f(1);
}
