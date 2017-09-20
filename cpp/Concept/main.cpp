#include <string>
#include <vector>

#include "Concepts.h"

namespace cp {

};

template<cp::Continer T>
void f(T ) {};

struct TestClass {
	constexpr TestClass() {};
	TestClass(const TestClass&) = default;
	TestClass& operator=(const TestClass&) = default;
	TestClass(const TestClass&&) {};
	TestClass& operator=(const TestClass&&) {return *this;};
	~TestClass() {};

	friend bool operator<(const TestClass&, const TestClass&) {
		return true;
	};

	friend bool operator==(const TestClass&, const TestClass&);

	int operator()()const {};

	int operator()(int, int)const {};
};

struct LockStruct {
	void lock() {};
	void unlock();
	bool try_lock() {return false;}
};


int main() {
	TestClass *t = 0;
	std::string s = "";
	// f(t);

	LockStruct lock;
	// f(lock);
	// f(1);
	std::vector<char> v;
	f(v);
}
