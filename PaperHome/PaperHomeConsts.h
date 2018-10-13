#pragma once

#include "defs.h"
#include <string>

using std::string;
using std::wstring;

class PaperHomeConsts {
public:
	static const string PaperHomeServerIP;
	static const WORD PaperHomeServerPort;
	static const DWORD PaperHomeTryToConnectInterval;
};