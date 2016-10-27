#pragma once

#include "resource.h"

#define HOTKEY_TRIGGER 0x00666
#define HOTKEY_EXIT 0x00999
#define TIMER_ID 0x00233

class ConfigurationWindow;

class AutoSnapshot :public CWinApp
{
private:
	ConfigurationWindow *configWindow;
	ULONG_PTR gdiplusToken;
	CString directoryPath;
public:
	BOOL InitInstance();
	int ExitInstance();	
	void doWork();
};