#include "stdafx.h"
#include "AutoSnapshot.h"
#include "Configuration.h"
#include "ConfigurationWindow.h"

BEGIN_MESSAGE_MAP(ConfigurationWindow, CDialogEx)
	ON_WM_TIMER()
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


ConfigurationWindow::ConfigurationWindow(AutoSnapshot *const app, Configuration *const config) : CDialogEx(IDD_CONFIG)
{
	mApp = app;
	mConfig = config;
}

void ConfigurationWindow::OnTimer(UINT_PTR nIDEvent)
{
	mApp->doWork();
	CDialog::OnTimer(nIDEvent);
}


void ConfigurationWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	mApp->doWork();
	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

BOOL ConfigurationWindow::OnInitDiaLog()
{
	return TRUE;
}

void ConfigurationWindow::initalizeConfiguration(const char * filePath)
{
	mFilePath = filePath;
	this->DoModal();
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
	bool timer_enabled = ((CButton*)GetDlgItem(IDC_CHK_TIMER))->GetCheck() == BST_CHECKED;
	bool hotkey_enabled = ((CButton*)GetDlgItem(IDC_CHK_HOTKEY))->GetCheck() == BST_CHECKED;
	bool encryption_enabled = ((CButton*)GetDlgItem(IDC_CHK_ENCRYPTION))->GetCheck() == BST_CHECKED;
	WORD code, modifiers;

	CString str;
	GetDlgItem(IDC_TXT_INTERVAL)->GetWindowText(str);
	if (timer_enabled && str == "") {
		MessageBox(_T("Interval cannot be empty!"));
		return;
	}
	if (str != "") {
		CStringA intervalAnsi(str);
		interval = atoi((const char *)intervalAnsi.GetString());
	}
	((CHotKeyCtrl*)GetDlgItem(IDC_HOTKEY))->GetHotKey(code, modifiers);
	if (hotkey_enabled && (code == 0 || modifiers == 0)) {
		MessageBox(_T("Hot key sequence cannot be empty!"));
		return;
	}
	if (!hotkey_enabled && !timer_enabled) {
		MessageBox(_T("Please choose at least one method!"));
		return;
	}
	mConfig->setValues(timer_enabled, interval, hotkey_enabled, modifiers, code, encryption_enabled);
	mConfig->writeIntoFile(mFilePath);
	CStringA notice;
	notice = "Configuration created. Will start running now.\n";
	notice += "To regenerate it, remove ";
	notice += mFilePath;
	MessageBoxA(GetSafeHwnd(), notice.GetString(), (LPCSTR)"Notice", 0);
	CDialog::OnOK();
}

void ConfigurationWindow::OnClose()
{
	return;
}

