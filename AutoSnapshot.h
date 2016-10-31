#pragma once

#define HOTKEY_TRIGGER 0x00666
#define HOTKEY_EXIT 0x00999
#define TIMER_ID 0x00233

class ConfigurationWindow;

class AutoSnapshot :public CWinApp

{
private:
	ULONG_PTR gdiplusToken;
	CString directoryPath;
public:
	BOOL InitInstance() override;
	int ExitInstance() override;	
	void doWork() const;
};