#ifndef CONCEPT_H__
#define CONCEPT_H__

#include <utility>
#include <type_traits>
#include <iterator>

namespace cp {

template<typename T>
concept bool EqualityComparable = requires(const T& a, const T& b) {
	{ a == b } -> bool;
	{ a != b } -> bool;
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
concept bool Iterator = requires(T iter) {
	typename std::iterator_traits<T>::value_type;
	typename std::iterator_traits<T>::difference_type;
	typename std::iterator_traits<T>::reference;
	typename std::iterator_traits<T>::pointer;
	typename std::iterator_traits<T>::iterator_category;
	{ *iter } -> typename std::iterator_traits<T>::reference;
	{ ++iter } -> T&;
};

template<class T>
concept bool InputIterator = requires(T iter, T i) {
	typename std::iterator_traits<T>::reference;
	{ iter != i } -> bool ;
	{ *iter } -> typename std::iterator_traits<T>::reference;
	{ iter++ } -> const T&;
	{ iter } -> typename std::iterator_traits<T>::pointer;
	{ *i++ } -> typename std::iterator_traits<T>::value_type;
} && Iterator<T> && EqualityComparable<T>;

template<class T>
concept bool OutputIterator = requires(T iter, T i,
const typename std::iterator_traits<T>::reference data) {
	{ *iter = data } -> typename std::iterator_traits<T>::reference;
	{ *iter++ = data } -> typename std::iterator_traits<T>::reference;
} && InputIterator<T>;

template<class T>
concept bool ForwardIterator = InputIterator<T> && DefaultConstructible<T>;

template<class T>
concept bool BidirectionalIterator = requires(T iter) {
	{ --iter } -> T&;
	{ iter-- } -> const T&;
	{ *iter-- } -> typename std::iterator_traits<T>::value_type;
} && ForwardIterator<T>;

template<class T>
concept bool RandomAccessIterator = requires(T iter, T i,
typename std::iterator_traits<T>::difference_type n) {
	typename std::iterator_traits<T>::difference_type;
	{ iter += n } -> T&;
	{ iter + n } -> T;
	{ n + iter } -> T;
	{ iter -= n } -> T&;
	{ iter - n } -> T;
	{ iter - i } -> typename std::iterator_traits<T>::difference_type;
	{ iter[n] } -> typename std::iterator_traits<T>::reference;
	{ iter < i } -> bool ;
	{ iter <= i } -> bool ;
	{ iter > i } -> bool ;
	{ iter >= i } -> bool ;
} && BidirectionalIterator<T>;

template<class T>
concept bool BasicLockable = requires(T mutex) {
	{ mutex.lock() };
	{ mutex.unlock() };
};


template<class T>
concept bool Lockable = requires(T mutex) {
	{ mutex.try_lock() } -> bool;
} && BasicLockable<T>;

template<class C>
concept bool Continer = requires(C c){
	typename C::value_type;
	typename C::reference;
	typename C::const_reference;
	typename C::iterator;
	typename C::const_iterator;
	typename C::difference_type;
	typename C::size_type;
	// { element } -> typename C::value_type;
	{ c.begin() } -> typename C::iterator;
	{ c.end() } -> typename C::iterator;
	{ c.cbegin() } -> typename C::const_iterator;
	{ c.cend() } -> typename C::const_iterator;
};


};

#endif
