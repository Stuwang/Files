#include<iostream>
#include<string>
#include<thread>

#include<Windows.h>

#include "base.h"


#define CHECK_RET(ret,FalseFlag,msg)         \
do{                                                    \
	if (FalseFlag == ret) {                              \
		std::cerr << msg << std::endl;           \
    return;                                  \
	}                                          \
}while(0);

void StartAChildProcess() {

	wchar_t CurrectDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, CurrectDir);

	LPTSTR ChildExePath = wcscat(CurrectDir, L"\\debug\\Simple.exe");

	STARTUPINFO si;
	base::DoZero(&si);
	PROCESS_INFORMATION pi;
	base::DoZero(&pi);

	BOOL CreateSuccess = CreateProcess(
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
	CHECK_RET(CreateSuccess, FALSE, "failed to create process");

	std::cout << "create process success" << std::endl;
	//		CloseHandle(pi.hProcess);
	//		CloseHandle(pi.hThread);

	Sleep(100);
	TerminateProcess(pi.hProcess, 300);
	//ExitProcess(1001);
}

static const wchar_t* kPipeName = L"\\\\.\\Pipe\\test";


struct PipHandle {
	HANDLE handle;
	HANDLE Event;
	OVERLAPPED ovlap;
	bool dataread;
	char buf[256];
	DWORD bytes;

	void ResetOP() {
		base::DoZero(&ovlap);
		ovlap.hEvent = Event;
	}
};

void StartMultiplePipServer() {
	static const int KPipSize = 5;

	HANDLE Event[KPipSize];
	PipHandle pips[KPipSize];

	for (size_t i = 0; i < KPipSize; i++) {
		pips[i].handle = CreateNamedPipe(
			kPipeName,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
			KPipSize,
			16*1024, 16 * 1024, 1000, NULL
		);
		// create error , return
		CHECK_RET(pips[i].handle, INVALID_HANDLE_VALUE, "Error Create");

		Event[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (NULL == Event[i]) {
			auto error = GetLastError();
			std::cerr << "Create Event Error" << error << std::endl;
			return;
		}

		pips[i].dataread = false;
		pips[i].bytes = 0;
		base::DoZero(pips[i].buf, ARRAY_SIZE(pips[i].buf));

		pips[i].Event = Event[i];
		pips[i].ResetOP();

		// async listen
		BOOL ret = ConnectNamedPipe(pips[i].handle, &pips[i].ovlap);
		if (FALSE == ret) {
			auto error = GetLastError();
			if (ERROR_IO_PENDING != error) {
				std::cerr << "connect error " << error << std::endl;
				return;
			}
			std::cout << "create is async" << std::endl;
		} else {
			std::cout << "create ok" << std::endl;
		}
	}

	std::cout << "ok server is running " << std::endl;

	while (true) {

		DWORD ret_index = WaitForMultipleObjects(KPipSize, Event, FALSE, INFINITE);
		CHECK_RET(ret_index, WAIT_FAILED, "error wait");

		auto PipIndex = ret_index - WAIT_OBJECT_0;

		auto &currect_pip = pips[PipIndex];

		//ResetEvent(Event[PipIndex]);

		// check results
		DWORD Bytes = 0;
		BOOL ret = GetOverlappedResult(currect_pip.handle, &currect_pip.ovlap, &currect_pip.bytes, TRUE);
		if (FALSE == ret) {
			std::cerr << "GetOverlappedResult error " << GetLastError() << std::endl;
			BOOL ret = DisconnectNamedPipe(currect_pip.handle);
			CHECK_RET(ret, FALSE, "error dis");

			// reconnect async listen
			ret = ConnectNamedPipe(currect_pip.handle, &currect_pip.ovlap);
			if (FALSE == ret) {
				auto error = GetLastError();
				if (ERROR_IO_PENDING != error) {
					std::cerr << "connect error " << error << std::endl;
					return;
				}
			}
			currect_pip.dataread = false;

		} else {
			// 立即执行了
			// not readed, read it
			//if (!currect_pip.dataread && 0 != currect_pip.bytes)
			{
				base::DoZero(&currect_pip.ovlap);
				currect_pip.ovlap.hEvent = Event[PipIndex];

				char buf[256] = { 0 };
				ret = ReadFile(currect_pip.handle, currect_pip.buf, ARRAY_SIZE(currect_pip.buf), NULL, &currect_pip.ovlap);
				if (FALSE == ret) {
					if (ERROR_IO_PENDING != GetLastError()) {
						std::cout << "read file error with error " << GetLastError() << std::endl;
					}
				}
				std::cout << "read :" << currect_pip.buf << std::endl;
				base::DoZero(currect_pip.buf, sizeof(currect_pip.buf));
				currect_pip.dataread = true;
			} 
//else if (0 != currect_pip.bytes) {
//				base::DoZero(&currect_pip.ovlap);
//				currect_pip.ovlap.hEvent = Event[PipIndex];
//				ret = WriteFile(currect_pip.handle, currect_pip.buf, currect_pip.bytes, NULL, &currect_pip.ovlap);
//				if (FALSE == ret) {
//					auto error = GetLastError();
//					if (ERROR_IO_PENDING != error) {
//						std::cout << "write file error " << error << error;
//					}
//				}
//				currect_pip.bytes = 0;
//				base::DoZero(&currect_pip.buf);
//				currect_pip.dataread = FALSE;
//			} else {
//				std::cout << "其他事件" << std::endl;
//			}
		}
	}
}

void StudyNamedPipeServer(const char* option) {
	HANDLE Pipe = CreateNamedPipe(kPipeName,
																PIPE_ACCESS_DUPLEX,
																PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
																PIPE_UNLIMITED_INSTANCES,
																16 * 1024,
																16 * 1024,
																1000,
																NULL
	);
	CHECK_RET(Pipe, INVALID_HANDLE_VALUE, "create handle error ");

	std::cout << "server is now running  " << std::endl;

	BOOL CallRet = ConnectNamedPipe(Pipe, NULL);
	CHECK_RET(CallRet, FALSE, "error connedted");

	while (true) {
		DWORD ReadBytes = 0;
		char Buf[1024] = { 0 };
		CallRet = ReadFile(Pipe, Buf, ARRAY_SIZE(Buf), &ReadBytes, NULL);
		CHECK_RET(CallRet, FALSE, "read file error");

		if (Buf == std::string("quit")) {
			break;
		}

		std::cout << "read " << ReadBytes << " bytes , content is " << Buf << std::endl;
	}

	CallRet = DisconnectNamedPipe(Pipe);
	CHECK_RET(CallRet, FALSE, "error DisconnectNamedPipe");

	CallRet = CloseHandle(Pipe);
	CHECK_RET(CallRet, FALSE, "error CloseHandle");
}

void StartNamesClient(const char* option) {
	BOOL ret = WaitNamedPipe(kPipeName, NMPWAIT_WAIT_FOREVER);
	CHECK_RET(ret, FALSE, "WaitNamedPipe error");

	HANDLE Pipe = CreateFile(kPipeName, PIPE_ACCESS_DUPLEX, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	CHECK_RET(Pipe, INVALID_HANDLE_VALUE, "CreateFile error");

	const char data[256] = "this is a client ";
	const size_t len = strlen(data);

	//DWORD WriteBytes = 0;
	//ret = WriteFile(Pipe, data, len, &WriteBytes, NULL);
	//CHECK_RET_OR_RETURN(ret, FALSE, "WriteFile error");

	//std::cout << "Write Bytes: " << WriteBytes << std::endl;

	while (true) {
		std::string input;
		std::cout << ">";
		std::cin >> input;
		if ("quit" == input) {
			std::cout << "quit" << std::endl;
			break;
		}

		DWORD WriteBytes = 0;
		ret = WriteFile(Pipe, input.data(), input.length(), &WriteBytes, NULL);
		CHECK_RET(ret, FALSE, "WriteFile error");

		std::cout << "send :" << input << std::endl;

		//read
		//char buf[1024] = { 0 };
		//DWORD bytes = 0;
		//auto ret = ReadFile(Pipe, buf, ARRAY_SIZE(buf), &bytes, NULL);
		//CHECK_RET(ret, FALSE, "read error");

		//std::cout << "read :" << buf << std::endl;
	}

	CHECK_RET(CloseHandle(Pipe), FALSE, "CLOSE error");
}

void NamedPipe(int type) {
	if (1 == type) {
		StartMultiplePipServer();
		//StudyNamedPipeServer(NULL);
	} else if (2 == type) {
		StartNamesClient(NULL);
	} else {
		std::cerr << "uknow flag" << std::endl;
	}
}

int main(int argc, const char* argv[])
{
	if (2 <= argc) {
		NamedPipe(2);
	} else {
		NamedPipe(1);
	}

	std::cout << "end " << std::endl;
	//std::cin.get();
	return 0;
}
