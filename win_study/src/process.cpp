#include<iostream>
#include<Windows.h>

#include "base.h"

void StartAChildProcess() {

	wchar_t CurrectDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, CurrectDir);

	LPTSTR ChildExePath = wcscat(CurrectDir, L"\\debug\\Simple.exe");

	STARTUPINFO si;
	base::DoZero(&si);
	PROCESS_INFORMATION pi;
	base::DoZero(&pi);

	bool CreateSuccess = CreateProcess(
		ChildExePath,
		NULL,
		NULL,
		NULL,
		false,
		NULL,
		NULL,
		NULL,
		&si,
		&pi
	);
	if (CreateSuccess) {
		std::cout << "create process success" << std::endl;
		//		CloseHandle(pi.hProcess);
		//		CloseHandle(pi.hThread);
	} else {
		std::cerr << "failed to create process" << std::endl;
	}

	Sleep(100);
	TerminateProcess(pi.hProcess, 300);
	//ExitProcess(1001);
}



int main()
{
	StartAChildProcess();
	std::cin.get();
	return 0;
}
