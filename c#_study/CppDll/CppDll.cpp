// CppDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include <iostream>
#include "CppDll.h"

// ���ǵ���������һ��ʾ��
CPPDLL_API int nCppDll=0;

// ���ǵ���������һ��ʾ����
CPPDLL_API int fnCppDll(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� CppDll.h
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
