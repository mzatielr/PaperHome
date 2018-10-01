#include "WinSockInfo.h"
#include "defs.h"
#include "define_exception.h"

WinSockInfo::WinSockInfo()
{
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	printf("Starting WSAStartup\n");
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		throw WsaStartupError();
	}
}
WinSockInfo::~WinSockInfo()
{
	printf("Deleting WinSockInfo\n");
	WSACleanup();
}
