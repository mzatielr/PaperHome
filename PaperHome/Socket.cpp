#include "Socket.h"

Socket::Socket(SOCKET socket) : m_underlyingSocket(socket), m_isClosed(false)
{
}

SOCKET Socket::getSocket()
{
	return m_underlyingSocket;
}

void Socket::close()
{
	if (!m_isClosed) {
		closesocket(m_underlyingSocket);
		m_isClosed = true;
	}
}

Socket::~Socket()
{
	close();
}
