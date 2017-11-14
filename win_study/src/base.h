#ifndef _BASE_H__
#define _BASE_H__

namespace base{

template<class T>
void DoZero(T * d) {
	memset(d, 0, sizeof(T));
}

}

#endif