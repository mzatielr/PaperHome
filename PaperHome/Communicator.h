#pragma once
#include "Socket.h"

class Communicator {
public:
	Communicator();
	bool tryConnect(std::string server_name, UINT server_port);
	void send_data(const char* buffer, DWORD buffer_len);
	void recv_data(int recv_buf_len, char* recv_buf);
	void disconnect();
	~Communicator();
private:
	void set_socket_opt(int level, int optname, const char* optval, int optlen);
	Socket m_ClientSocket;
	bool m_isConnected;
};