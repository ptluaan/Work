#pragma once
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <shlobj.h>
#include <map>
#include <Shlwapi.h>

#pragma comment(lib,"shlwapi.lib") 
//#include "HashWinAPI.h"
#include "WindowLogin.h"
#include "WindowMainApp.h"

#define DISTANCE_UNIT 35
#define WIDTH_UNIT 20
#define ALIGN 20
#define ALIGN_R 2.8

void showAndHandleWindow(HWND hwnd);
std::wstring getFileNameW(const std::wstring& path);

int nCmdShow;
HINSTANCE hInstance;
