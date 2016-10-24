#include "stdafx.h"
#include "AutoSnapshot.h"
#include "IniFile.h"

#pragma comment(lib, "gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;          // number of image encoders
	UINT size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1;  // Failure
	}

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
	{
		return -1;  // Failure
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

void BitmapToJpg(HBITMAP hbmpImage, int width, int height, LPCWSTR filename, ULONG uQuality)
{
	Gdiplus::Bitmap *p_bmp = Gdiplus::Bitmap::FromHBITMAP(hbmpImage, NULL);

	CLSID pngClsid;
	Gdiplus::EncoderParameters encoderParams;
	encoderParams.Count = 1;
	encoderParams.Parameter[0].NumberOfValues = 1;
	encoderParams.Parameter[0].Guid = Gdiplus::EncoderQuality;
	encoderParams.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
	encoderParams.Parameter[0].Value = &uQuality;
	int result = GetEncoderClsid(L"image/jpeg", &pngClsid);
	if (result != -1)
		std::cout << "Encoder succeeded" << std::endl;
	else
		std::cout << "Encoder failed" << std::endl;
	p_bmp->Save(filename , &pngClsid, &encoderParams);
	//TODO make the file unable to be opened directly,
	//such as modify the JPEG file header (the first 9 bytes) and change the file extension
	delete p_bmp;
}

bool ScreenCapture(int x, int y, int width, int height, LPCWSTR filename, ULONG uQuality)
{
	HDC hDc = CreateCompatibleDC(0);
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
	BitmapToJpg(hBmp, width, height, filename, uQuality);
	DeleteObject(hBmp);
	return true;
}

void getDirectoryPath(CString &strCurPath) {
	GetModuleFileName(NULL, strCurPath.GetBuffer(MAX_PATH), MAX_PATH);
	strCurPath.ReleaseBuffer();
	int pos = strCurPath.ReverseFind(_T('\\'));
	strCurPath = strCurPath.Left(pos + 1);
}

void getNowTime(char *buffer) {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	sprintf_s(buffer, 20, "%4d-%02d-%02d-%02d-%02d-%02d",
				sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
}

//TODO add a global hotkey to call this function
void timerWork(CString filename)
{
	char *time = new char[20];
	getNowTime(time);
	filename += time;
	filename += ".dump";
	//TODO obscure the file name and directory path

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	std::cout << filename.GetString() << std::endl;
	ScreenCapture(0, 0, width, height, filename.GetString(), 100L);
	
	delete time;
}

int _real_main() {
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CString filename;
	getDirectoryPath(filename);

	CString configPath = filename + "snap_config.ini";
	CFileFind finder;   //will create a new one if not exists
	BOOL ifFind = finder.FindFile(configPath.GetString());
	if (!ifFind)
	{
		//TODO require user to do configuration
	}
	

	CIniFile iniFile(configPath.GetString(), 4096);

	while (true) {
		timerWork(filename);
		Sleep(5000);
		//TODO make the time duration adjustable
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

/*
Please note that this is the real entry point of the funcion as an Win32 application.
If you directly use main() and compile it as an console application, the console window will
always show up at startup. Even if you hide it in the first line of code, it will still cause
an unpleasing flash of black window and will be noticed.
*/
int __stdcall _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	//TODO add an window to configure the behavior if no configuration file exists.
	_real_main();
}
