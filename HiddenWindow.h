#pragma once

#include "stdafx.h"
#include "AutoSnapshot.h"
#include "HiddenWindow.h"

class AutoSnapshot;

class HiddenWindow : public CFrameWnd {

public:
	HiddenWindow(AutoSnapshot *const app);
	void OnTimer(UINT_PTR nIDEvent);
	void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

	DECLARE_MESSAGE_MAP();

private:
	AutoSnapshot *mApp;

};