#pragma once
#include "stdafx.h"


class AutoSnapshot;
class Configuration;

class ConfigurationWindow :public CDialogEx
{
private:
	AutoSnapshot *mApp;
	Configuration *mConfig;
	const char* mFilePath;

public:
	ConfigurationWindow(AutoSnapshot * const app, Configuration *const config);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDiaLog();
	void initalizeConfiguration(const char* filePath);
	

	DECLARE_MESSAGE_MAP()
};