#include "defs.h"

#include "PaperHomeConsts.h"
#include "WinSockInfo.h"
#include "Communicator.h"

int main() {
	try
	{
		printf("Starting PaperHome\n");
		WinSockInfo wsa_info;
		Communicator commicator;
		while (true) {
			try {
				Sleep(PaperHomeConsts::PaperHomeTryToConnectInterval);
				commicator.tryConnect(PaperHomeConsts::PaperHomeServerIP, PaperHomeConsts::PaperHomeServerPort);
			}
			catch (std::exception& exception) {
				printf("Caught exception: %s\n", exception.what());
			}
		}

	}
	catch (...) {
		printf("Unhandled exception has been thrown\n");
	}
	return 0;
}