#include "Communicator.h"
#include "defs.h"
#include <exception> 

Communicator::Communicator() : m_ClientSocket(INVALID_SOCKET), m_isConnected(false) {
	SOCKET client_socket = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		throw std::exception("socket failed");
	}

	int recv_send_timeout = 500;
	set_socket_opt(SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&recv_send_timeout), sizeof(int));
	set_socket_opt(SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&recv_send_timeout), sizeof(int));
	
	BOOL bOptVal = TRUE;
	set_socket_opt(SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char*>(&bOptVal), sizeof(BOOL));

	m_ClientSocket.setSocket(client_socket);
}

void Communicator::set_socket_opt(int level, int optname, const char * optval, int optlen) {
	int result = setsockopt(m_ClientSocket.getSocket(), level, optname, optval, optlen);
	if (result == SOCKET_ERROR) {
		printf("set socket failed %d\n", WSAGetLastError());
		throw std::exception("set socket failed");
	}
}

void Communicator::disconnect()
{
	if (!m_isConnected) {
		printf("Socket is already disconnected\n");
	}

	INT result = shutdown(m_ClientSocket.getSocket(), SD_BOTH);
	if (result == SOCKET_ERROR) {
		printf("Shutdown failed with error %d\n", WSAGetLastError());
	}
	m_isConnected = false;
}

bool Communicator::tryConnect(std::string server_name, UINT server_port) {
	if (m_isConnected) {
		printf("Socket already connected\n");
		return true;
	}

	ADDRINFOA hints = { 0 };
	PADDRINFOA result = nullptr;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	INT status = GetAddrInfo("10.0.0.2", std::to_string(server_port).c_str(), &hints, &result);
	if (status != 0) {
		printf("getaddrinfo failed with error: %d\n", status);
		throw std::exception("getaddrinfo failed");
	}

	PADDRINFOA ptr = nullptr;
	SOCKET connect_socket = m_ClientSocket.getSocket();
	for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
		status = connect(connect_socket, ptr->ai_addr, ptr->ai_addrlen);
		if (status == SOCKET_ERROR) {
			printf("connect failed with error: %ld\n", WSAGetLastError());
			FreeAddrInfo(result);
			m_isConnected = false;
			return m_isConnected;
		}
		break;
	}
	FreeAddrInfo(result);
	m_isConnected = true;
	return m_isConnected;
}

void Communicator::send_data(const char * buffer, DWORD buffer_len) {
	if (!m_isConnected) {
		throw std::exception("Cannot send buffer because, socket is not connected");
	}
	INT result = send(m_ClientSocket.getSocket(), buffer, buffer_len, 0);
	if (result == SOCKET_ERROR) {
		disconnect();
		printf("Failed to send data, error: %d. Disconnecting socket\n");
		throw std::exception("Failed to send data");
	}
}

void Communicator::recv_data(int recv_buf_len, char * recv_buf)
{
	if (!m_isConnected) {
		throw std::exception("Cannot recv data, because socket isn't connected");
	}
	INT result = recv(m_ClientSocket.getSocket(), recv_buf, recv_buf_len, 0);
	if (result != recv_buf_len) {
		printf("Failed to recv data, error: %d. Disocnnecting socket\n", WSAGetLastError());
		disconnect();
		throw std::exception("Failed to recv data");
	}
}

Communicator::~Communicator() {
	if (!m_isConnected) {
		try {
			disconnect();
		}
		catch (std::exception& ex) {
			printf(ex.what());
		}
		catch (...) {
			printf("Execption has been throwm during disconnecting socket");
		}
	}
}