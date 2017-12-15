//#include <Windows.h>

#include <vector>

#include "net_exp.h"

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <stdio.h>


typedef SOCKET socket_type;
typedef HANDLE iocp_port_type;

union SOCKET_HANDLE {

	/*  The actual underlying socket. Can be used as a HANDLE too. */
	socket_type s;

	/*  Named pipe handle. Cannot be used as a SOCKET. */
	HANDLE p;
};

// create a new socket , and bind it to iocp port
socket_type CreateSocketWithIocp(iocp_port_type iocp_port, bool Bind = false) {
	SOCKET_HANDLE s;

	// The socket that is created will have the overlapped attribute as a default. 
	// https://msdn.microsoft.com/en-us/library/ms740506(v=vs.85).aspx
	s.s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == s.s) {
		LOG_FATAL(GetStdLogger()) << "error socket , create accepter : " << GetLastError();
	}

	if (Bind) {
		HANDLE ret_register = CreateIoCompletionPort(s.p, iocp_port, 0, NULL);
		if (NULL == ret_register) {
			LOG_FATAL(GetStdLogger()) << "error register the accept socket to IOCP port " << GetLastError();
		}
	}

	return s.s;
}

socket_type BindToIocp(iocp_port_type iocp_port, socket_type so) {
	SOCKET_HANDLE s;
	s.s = so;
	HANDLE ret_register = CreateIoCompletionPort(s.p, iocp_port, 0, NULL);
	if (NULL == ret_register) {
		LOG_FATAL(GetStdLogger()) << "error register the accept socket to IOCP port " << GetLastError();
	}
	return s.s;
}

struct AcceptFunc {
	LPFN_ACCEPTEX lpfnAcceptEx = NULL;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;

	AcceptFunc(socket_type ls) {

		//
		// what the fuck ?!!!
		//
		// Load the AcceptEx function into memory using WSAIoctl.
		// The WSAIoctl function is an extension of the ioctlsocket()
		// function that can use overlapped I/O. The function's 3rd
		// through 6th parameters are input and output buffers where
		// we pass the pointer to our AcceptEx function. This is used
		// so that we can call the AcceptEx function directly, rather
		// than refer to the Mswsock.lib library.
		DWORD dwBytes = 0;
		auto iResult = WSAIoctl(ls, SIO_GET_EXTENSION_FUNCTION_POINTER,
											 &GuidAcceptEx, sizeof(GuidAcceptEx),
											 &lpfnAcceptEx, sizeof(lpfnAcceptEx),
											 &dwBytes, NULL, NULL);
		if (iResult == SOCKET_ERROR) {
			wprintf(L"WSAIoctl failed with error: %u\n", WSAGetLastError());
			closesocket(ls);
			WSACleanup();
		}
	}
};

void StartIocpServer() {

	WSADATA wsaData;
	auto iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("Error at WSAStartup\n");
		return;
	}

	iocp_port_type iocp_port;

	iocp_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (NULL == iocp_port) {
		LOG_FATAL(GetStdLogger()) << "error CreateIoCompletionPort " << GetLastError();
	}

	socket_type accepter = CreateSocketWithIocp(iocp_port, true);

	sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(27015);

	int rc = bind(accepter, (sockaddr*)&addr, sizeof(sockaddr_in));
	if (SOCKET_ERROR == rc) {
		LOG_FATAL(GetStdLogger()) << "bind error " << GetLastError();
	}

	rc = listen(accepter, 10);
	if (SOCKET_ERROR == rc) {
		LOG_FATAL(GetStdLogger()) << "listen error " << GetLastError();
	}

	socket_type new_socket = CreateSocketWithIocp(iocp_port);

	AcceptFunc accept_f(accepter);

	OVERLAPPED accept_oap;
	base::DoZero(&accept_oap);

	char accept_addr[512] = { 0 };
	// when we set the dwReceiveDataLength to zero, this param is always set to zero.
	DWORD recive_byte = 0;


	BOOL accept_success = accept_f.lpfnAcceptEx(accepter, new_socket,
																 accept_addr, 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &recive_byte,
																 &accept_oap);
	if (FALSE == accept_success) {
		if (WSAGetLastError() == ERROR_IO_PENDING) {
			LOG_DEBUG(GetStdLogger()) << "what £¿" ;
		}
	}

	for (;;) {
		static const int KEntrySize = 32;
		OVERLAPPED_ENTRY entrys[KEntrySize] = { 0 };
		ULONG ret_size = 0;
		BOOL ret = GetQueuedCompletionStatusEx(iocp_port, entrys, KEntrySize, &ret_size, INFINITE, FALSE);
		if (FALSE == ret) {
			auto error = GetLastError();
			LOG_FATAL(GetStdLogger()) << "error in wait for operations, error " << error;
		}
		for (size_t i = 0; i < ret_size; i++){
			auto p = entrys + i;
			// this is a new accepted socket
			if (p->lpOverlapped == &accept_oap) {


				LOG_DEBUG(GetStdLogger()) << "get a new socket , now close it ";
				LOG_DEBUG(GetStdLogger()) << "bytes transerfed is " << p->dwNumberOfBytesTransferred;
				LOG_DEBUG(GetStdLogger()) << "error code is " << p->Internal;

				sockaddr_in* localaddr = reinterpret_cast<sockaddr_in*>(accept_addr);
				sockaddr_in* peer = reinterpret_cast<sockaddr_in*>(static_cast<char*>(accept_addr) + sizeof(sockaddr_in) + 16);

				LOG_DEBUG(GetStdLogger()) << "local port : " << ntohs(localaddr->sin_port);
				LOG_DEBUG(GetStdLogger()) << "peer  port : " << ntohs(peer->sin_port);

				::closesocket(new_socket);
				new_socket = CreateSocketWithIocp(iocp_port);

				base::DoZero(&accept_oap);
				BOOL accept_success = accept_f.lpfnAcceptEx(accepter, new_socket,
																										accept_addr, 0, 256, 256, &recive_byte,
																										&accept_oap);
			} else {

			}
		}
	}
}


// this is a new project use IOCP
// now , don't attention it .

//class socket_handle {};
//class accepter{};
//class service{};
//class timer{};
//class op_base{};
//class op_accept{};
//class op_connect{};
//class op_send{};
//class op_receive{};

class Accepter {
public:
	int Bind(const std::string& ip, int port) {
		return 0;
	};

	void AsyncConnect(int errorcode, SOCKET s) {

	}
};

class Service {

	Service() {
		HANDLE iocp_port;

		iocp_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (NULL == iocp_port) {
			LOG_FATAL(GetStdLogger()) << "error CreateIoCompletionPort " << GetLastError();
		}
	}

	// 0 success, else error code
	int AddInService(SOCKET s) {
		auto ret = CreateIoCompletionPort((HANDLE)s, iocp_port, NULL, 0);
		if (NULL == ret) {
			LOG_FATAL(GetStdLogger()) << "CreateIoCompletionPort Error " << GetLastError();
			return GetLastError();
		}
		return 0;
	}

	int Run() {
		ULONG count = entrys.size();
		int ret = GetQueuedCompletionStatusEx(iocp_port,
																					entrys.data(),
																					entrys.size(),
																					&count,
																					INFINITE,
																					false);
	}


private:
	HANDLE iocp_port;
	std::vector<OVERLAPPED_ENTRY> entrys;

	NO_COPY_AND_ASSIGN(Service)
};

class Connection {

};



