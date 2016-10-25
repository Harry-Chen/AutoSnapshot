#include "stdafx.h"
#include "Configuration.h"
#include "AutoSnapshot.h"
#include "ConfigurationWindow.h"
#include "Utilities.h"
#include "HiddenWindow.h"

Configuration config;

BOOL AutoSnapshot::InitInstance()
{
	configWindow = new ConfigurationWindow(this, &config);
	m_pMainWnd = new HiddenWindow(this);

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	getDirectoryPath(directoryPath);


	CString configPath = directoryPath + "snap_config.json";
	CFileFind finder;
	BOOL ifFind = finder.FindFile(configPath.GetString());
	CStringA configPathAnsi(configPath);
	const char* pathForJson = configPathAnsi.GetString();

	if (!ifFind)
	{
		configWindow->initalizeConfiguration(pathForJson);
	}

	bool result = config.parseFromFile(pathForJson);
	if (config.isTimerEnabled()) {
		SetTimer(*m_pMainWnd, TIMER_ID, config.getTimerInterval(), NULL);

	}
	if (config.isHotKeyEnabled()) {
		RegisterHotKey(*m_pMainWnd, HOTKEY_ID, config.getHotKeyModifiers(), config.getHotKeyCode());
	}
	return TRUE;

}

int AutoSnapshot::ExitInstance() {
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

void AutoSnapshot::doWork() {
	work(directoryPath, config.isEncryptionEnabled());
}

AutoSnapshot theApp;