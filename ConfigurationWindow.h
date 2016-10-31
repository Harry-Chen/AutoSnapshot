#pragma once
#include "stdafx.h"


class AutoSnapshot;
class Configuration;

class ConfigurationWindow :public CDialogEx
{
private:
	Configuration *mConfig;
	const char* mFilePath;

public:
	ConfigurationWindow(Configuration *const config, const char * filePath);
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	BOOL PreTranslateMessage(MSG* pMsg) override;
	BOOL OnInitDiaLog();
	
	DECLARE_MESSAGE_MAP()
};