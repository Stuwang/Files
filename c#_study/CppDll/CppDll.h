// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CPPDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CPPDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef CPPDLL_EXPORTS
#define CPPDLL_API __declspec(dllexport)
#else
#define CPPDLL_API __declspec(dllimport)
#endif

#if defined( __cplusplus)
extern "C"{
#endif
// �����Ǵ� CppDll.dll ������
class CPPDLL_API CCppDll {
public:
	CCppDll(void);
	// TODO:  �ڴ�������ķ�����
};

extern CPPDLL_API int nCppDll;

CPPDLL_API int fnCppDll(void);

CPPDLL_API const char* GetString();

CPPDLL_API void _stdcall Print(const char* data);

#if defined( __cplusplus)
}
#endif