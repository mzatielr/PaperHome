#pragma once
#include "defs.h"
class Socket {
public:
	Socket(SOCKET socket);
	SOCKET getSocket();
	void close();
	~Socket();
private:
	SOCKET m_underlyingSocket;
	bool m_isClosed;
};