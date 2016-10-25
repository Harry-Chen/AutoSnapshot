#include "stdafx.h"
#include "AutoSnapshot.h"
#include "HiddenWindow.h"

BEGIN_MESSAGE_MAP(HiddenWindow, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


HiddenWindow::HiddenWindow(AutoSnapshot *const app)
{
	mApp = app;
	Create(NULL, NULL);
}

void HiddenWindow::OnTimer(UINT_PTR nIDEvent)
{
	mApp->doWork();
	CFrameWnd::OnTimer(nIDEvent);
}


void HiddenWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	mApp->doWork();
	CFrameWnd::OnHotKey(nHotKeyId, nKey1, nKey2);
}
