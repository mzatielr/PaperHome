#include "defs.h"
#include "WinSockInfo.h"

int main() {
	try
	{
		printf("Starting PaperHome\n");
		WinSockInfo();
	}
	catch (...) {
		printf("Unhandled exception has been thrown\n");
	}
	return 0;
}