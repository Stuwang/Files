#ifndef _BASE_H__
#define _BASE_H__

#include <cstring>

namespace base{

template<class T>
void DoZero(T * d) {
	memset(d, 0, sizeof(T));
}

inline void DoZero(void *dst, size_t size) {
	memset(dst, 0, size);
}

}


template<class T, size_t N>
char(&_array_size_helper( /*in */  T(&array)[N]))[N] {
	return static_cast<char(&)[N]>(0);
};

#define ARRAY_SIZE(arr) (sizeof(_array_size_helper(arr)))


#endif