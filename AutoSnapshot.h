#pragma once

#include "resource.h"

#define HOTKEY_ID 0x00001
#define TIMER_ID 0x00233

class ConfigurationWindow;

class AutoSnapshot :public CWinApp
{
private:
	ConfigurationWindow *wnd;
	ULONG_PTR gdiplusToken;
	CString directoryPath;
public:
	BOOL InitInstance();
	int ExitInstance();	
	void doWork();
};