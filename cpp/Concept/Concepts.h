#ifndef CONCEPT_H__
#define CONCEPT_H__

#include <utility>
#include <type_traits>

namespace cp {

template<typename T>
concept bool EqualityComparable = requires(const T& a, const T& b) {
	{ a == b } -> bool;
};

template<typename T>
concept bool LessThanComparable = requires(const T& a, const T& b) {
	{ a < b } -> bool;
	{ b < a } -> bool;
};

using std::swap;
template<class T>
concept bool Swappable = requires(T a, T b) {
	{ swap(a, b) };
	{ swap(b, a) };
};

template<class T, class R, class ...Args>
concept bool Callable = requires(const T& call, Args... args) {
	{ call(args...) } -> R;
};

template<class T>
concept bool Predicate = Callable<T, bool>;

template<class T, class Arg>
concept bool BinaryPredicate = Callable<T, bool, Arg>;

template<class T, class C>
concept bool Compare = Callable<T, bool, C, C>;

template<class T>
concept bool DefaultConstructible = requires() {
	{ T() } -> T;
	{ T{} } -> T;
};

template<class T>
concept bool MoveConstructible = requires(T && t) {
	{ T(std::move(t)) } -> T;
};

template<class T>
concept bool CopyConstructible = requires(const T& t) {
	{ T(t) } -> T;
};

template<class T>
concept bool Destructible = requires(T t) {
	{ t.~T() }
};

template<class T>
concept bool MoveAssignable  = requires(T l, T r) {
	{ l = std::move(r) } -> T&;
};

template<class T>
concept bool CopyAssignable = requires(T l, const T& r) {
	{ l = r } -> T&;
};

template<class T>
const bool Iterator = requires(){
	using value_type = typename std::iterator_traits<T>::value_type;

	// value_type, difference_type, reference, pointer, and iterator_category 
}

};

#endif
