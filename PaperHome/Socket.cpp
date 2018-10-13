#include "Socket.h"

#include <exception>

Socket::Socket(SOCKET socket) : m_underlyingSocket(socket), m_isClosed(false), m_isSocketSet(false)
{
	m_isSocketSet = (m_underlyingSocket != INVALID_SOCKET);
}


SOCKET Socket::getSocket()
{
	return m_underlyingSocket;
}

void Socket::setSocket(SOCKET socket)
{
	if (m_isSocketSet) {
		throw std::exception("Socket was already set");
	}

	m_underlyingSocket = socket;
}

void Socket::close()
{
	if (!m_isClosed && m_isSocketSet) {
		closesocket(m_underlyingSocket);
		m_isClosed = true;
	}
}

Socket::~Socket()
{
	close();
}
