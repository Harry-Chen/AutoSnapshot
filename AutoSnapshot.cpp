#include "stdafx.h"
#include "Configuration.h"
#include "AutoSnapshot.h"
#include "ConfigurationWindow.h"
#include "Utilities.h"
#include "HiddenWindow.h"

Configuration config;
CFileFind finder;

BOOL AutoSnapshot::InitInstance()
{
	m_pMainWnd = new HiddenWindow(this);

	//Use Ctrl+Alt+Shift+X to exit
	//TODO not working
	RegisterHotKey(*m_pMainWnd, HOTKEY_EXIT, MOD_ALT | MOD_SHIFT, 'z');

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	getDirectoryPath(directoryPath);

	CString configPath = directoryPath + "snap_config.json";
	CStringA configPathAnsi(configPath);
	auto pathForJson = configPathAnsi.GetString();

	if (!finder.FindFile(configPath.GetString()))
	{
		auto configWindow = new ConfigurationWindow(&config, pathForJson);
		configWindow->DoModal();
	}

	config.parseFromFile(pathForJson);

	if (config.isEncryptionEnabled()) {
		hideFile(configPath.GetString());
		directoryPath += config.getRandomDirectory().c_str();
	}
	
	if (config.isTimerEnabled()) {
		SetTimer(*m_pMainWnd, TIMER_ID, config.getTimerInterval(), nullptr);

	}

	if (config.isHotKeyEnabled()) {
		RegisterHotKey(*m_pMainWnd, HOTKEY_TRIGGER, config.getHotKeyModifiers(), config.getHotKeyCode());
	}

	return TRUE;

}

int AutoSnapshot::ExitInstance(){
	Gdiplus::GdiplusShutdown(gdiplusToken);
	if (config.isTimerEnabled()) {
		KillTimer(*m_pMainWnd, TIMER_ID);
	}
	if (config.isHotKeyEnabled()) {
		UnregisterHotKey(*m_pMainWnd, HOTKEY_TRIGGER);
	}
	UnregisterHotKey(*m_pMainWnd, HOTKEY_EXIT);
	return 0;
}

void AutoSnapshot::doWork() const{
	auto path = directoryPath.GetString();
	if (!finder.FindFile(path)) {
		//This only happens when encryption is on
		//Let's hide the directories level by level
		SHCreateDirectoryEx(nullptr, path, nullptr);
		hideFile(path);
		auto pos = directoryPath.GetLength() - 11;
		hideFile(directoryPath.Left(pos).GetString());
	}
	work(directoryPath, config.isEncryptionEnabled());
}

AutoSnapshot theApp;