#include "stdafx.h"
#include "AutoSnapshot.h"
#include "Configuration.h"
#include "ConfigurationWindow.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(ConfigurationWindow, CDialogEx)
	ON_WM_TIMER()
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


ConfigurationWindow::ConfigurationWindow(Configuration *const config, const char * filePath) : CDialogEx(IDD_CONFIG)
{
	mConfig = config;
	mFilePath = filePath;
}

BOOL ConfigurationWindow::OnInitDiaLog()
{
	return TRUE;
}

BOOL ConfigurationWindow::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void ConfigurationWindow::OnBnClickedOk()
{
	UINT interval = 0L;
	auto timer_enabled = ((CButton*)GetDlgItem(IDC_CHK_TIMER))->GetCheck() == BST_CHECKED;
	auto hotkey_enabled = ((CButton*)GetDlgItem(IDC_CHK_HOTKEY))->GetCheck() == BST_CHECKED;
	auto encryption_enabled = ((CButton*)GetDlgItem(IDC_CHK_ENCRYPTION))->GetCheck() == BST_CHECKED;
	WORD code, modifiers;

	CString str;
	GetDlgItem(IDC_TXT_INTERVAL)->GetWindowText(str);
	if (timer_enabled && str == "") {
		MessageBox(_T("请输入间隔时间"), _T("错误"));
		return;
	}
	if (str != "") {
		CStringA intervalAnsi(str);
		interval = atoi((const char *)intervalAnsi.GetString());
	}
	((CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY))->GetHotKey(code, modifiers);
	if (hotkey_enabled && (code == 0 || modifiers == 0)) {
		MessageBox(_T("请指定快捷键"), _T("错误"));
		return;
	}
	if (!hotkey_enabled && !timer_enabled) {
		MessageBox(_T("请至少使用一种触发方式"), _T("错误"));
		return;
	}

	std::string prefix;
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < 10; ++i)
		prefix += 'A' + (rand() % 26);
	prefix += '\\';
	for (int i = 0; i < 10; ++i)
		prefix += 'A' + (rand() % 26);
	prefix += '\\';

	mConfig->setValues(timer_enabled, interval, hotkey_enabled, modifiers, code, encryption_enabled, prefix);
	mConfig->writeIntoFile(mFilePath);
	CStringA notice;
	notice = "配置成功，点击“确认”开始运行\n";
	notice += "若要重新配置，请删除";
	notice += mFilePath;
	MessageBoxA(GetSafeHwnd(), notice.GetString(), (LPCSTR)"提醒", 0);
	CDialog::OnOK();
}

void ConfigurationWindow::OnClose()
{
	MessageBox(_T("配置未完成，程序将立刻退出"), _T("提醒"));
	CDialogEx::OnClose();
}

