#pragma once
#include "stdafx.h"

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

void BitmapToJpg(HBITMAP hbmpImage, int width, int height, LPCWSTR filename, ULONG uQuality);

void getDirectoryPath(CString &strCurPath);

void getNowTime(char *buffer);

bool ScreenCapture(int x, int y, int width, int height, LPCWSTR filename, ULONG uQuality);

void fillJpegHeaderWithZero(LPCTSTR filename);

void work(CString filename, bool encryption);

