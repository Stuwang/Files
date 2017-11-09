// CppDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include <iostream>
#include "CppDll.h"

// 这是导出变量的一个示例
CPPDLL_API int nCppDll=0;

// 这是导出函数的一个示例。
CPPDLL_API int fnCppDll(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 CppDll.h
CCppDll::CCppDll()
{
	return;
}

CPPDLL_API const char* GetString(){
  return "test in this dll GetString";
};

CPPDLL_API void _stdcall Print(const char* data){
  std::cout << "cout in this dll Print " << data << std::endl;
};
