#include "stdafx.h"
#include "AutoSnapshot.h"
#include "ConfigurationWindow.h"

BEGIN_MESSAGE_MAP(ConfigurationWindow, CFrameWnd)
ON_WM_TIMER()
ON_WM_HOTKEY()
END_MESSAGE_MAP()


ConfigurationWindow::ConfigurationWindow(AutoSnapshot *const app)
{
	mApp = app;
	Create(NULL, _T("This is configuration"));
}

void ConfigurationWindow::OnTimer(UINT_PTR nIDEvent)
{
	mApp->doWork();
	CFrameWnd::OnTimer(nIDEvent);
}


void ConfigurationWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	mApp->doWork();
	CFrameWnd::OnHotKey(nHotKeyId, nKey1, nKey2);
}
