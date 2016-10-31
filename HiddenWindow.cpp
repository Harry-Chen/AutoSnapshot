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
	CFrameWnd::Create(nullptr, nullptr);
}

void HiddenWindow::OnTimer(UINT_PTR nIDEvent)
{
	mApp->doWork();
	CFrameWnd::OnTimer(nIDEvent);
}


void HiddenWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	switch (nHotKeyId) {
	case HOTKEY_TRIGGER:
		mApp->doWork();
		break;
	case HOTKEY_EXIT:
		PostMessage(WM_QUIT);
		break;
	default:
		break;
	}

	CFrameWnd::OnHotKey(nHotKeyId, nKey1, nKey2);
}
