#include "stdafx.h"
#include "Configuration.h"
#include "AutoSnapshot.h"
#include "ConfigurationWindow.h"
#include "Utilities.h"


BOOL AutoSnapshot::InitInstance()
{
	wnd = new ConfigurationWindow(this);

	m_pMainWnd = wnd;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	getDirectoryPath(directoryPath);

	Configuration config;
	CString configPath = directoryPath + "snap_config.json";
	CFileFind finder;
	BOOL ifFind = finder.FindFile(configPath.GetString());

	//Enable the triggers for debugging
	SetTimer(*m_pMainWnd, TIMER_ID, 5000L, NULL);
	RegisterHotKey(*m_pMainWnd, HOTKEY_ID, MOD_ALT | MOD_SHIFT, 'X');

	if (!ifFind)
	{
		//TODO require user to do configuration

	}
	else {
		bool result = config.parseFromFile((const char*)configPath.GetString());
		if (!result) {
			//TODO corrput configuration, require user to do configuration
		}
		if (config.isTimerEnabled()) {
			SetTimer(*m_pMainWnd, TIMER_ID, config.getTimerInterval(), NULL);

		}
		if (config.isHotKeyEnabled()) {
			RegisterHotKey(*m_pMainWnd, HOTKEY_ID, config.getHotKeyModifiers(), config.getHotKeyCode());
		}
	}

	m_pMainWnd->ShowWindow(SW_SHOW);
	return TRUE;

}

int AutoSnapshot::ExitInstance() {
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

void AutoSnapshot::doWork() {
	work(directoryPath);
}

AutoSnapshot theApp;