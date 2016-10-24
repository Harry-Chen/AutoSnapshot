#pragma once
#include "stdafx.h"


class AutoSnapshot;
class ConfigurationWindow :public CFrameWnd
{
private:
	AutoSnapshot *mApp;

public:
	ConfigurationWindow(AutoSnapshot * const app);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

	DECLARE_MESSAGE_MAP()
};