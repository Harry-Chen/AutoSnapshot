#pragma once

#include "targetver.h"

#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxdialogex.h>
#include <gdiplus.h>
#include <Shlobj.h>
#include <iostream>
#include <fstream>

//MS has defined two macros in windows.h, causing the function in STL with the same names not to work.
#undef min
#undef max

#include "json/json.h"
#include "json/json-forwards.h"
