#include "MainApp.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,

	LPSTR lpCmdLine, int nCmdShow)
{
	::hInstance = hInstance;
	::nCmdShow = nCmdShow;
	if (loginApp())
	doApp();

	return 0;//(int)msg.wParam;
}
void doApp()
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.lpszClassName = TEXT("MainApp");
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClass(&wc);
	hwndApp = CreateWindowA(wc.lpszClassName, "CHAT", WS_CAPTION | WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH_MAIN_APP, HEIGHT_MAIN_APP, NULL, NULL, hInstance, NULL);

	if (!hwndApp) {
		MessageBox(NULL, TEXT("Could not create main window"), NULL, MB_ICONERROR);
		return;
	}

	showAndHandleWindow(hwndApp);
}

bool loginApp()
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	wc.lpszClassName = TEXT("Login");
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProcLogin;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClass(&wc);
	hwndLogin = CreateWindowA(wc.lpszClassName, "Login", WS_CAPTION | WS_SYSMENU | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH_LOGIN, HEIGHT_LOGIN, NULL, NULL, hInstance, NULL);

	if (!hwndLogin) {
		MessageBox(NULL, TEXT("Could not create login window"), NULL, MB_ICONERROR);
		return 0;
	}

	showAndHandleWindow(hwndLogin);

	return loginSuccess;
}

void showAndHandleWindow(HWND hwnd)
{
	MSG  msg;
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

LRESULT CALLBACK WndProcLogin(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		createWindowLogin(hwnd, lParam);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (LOWORD(wParam))
			{
			case BUTTON_LOGIN:
				handleButtonLogin();

			}
			//InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		createWindowMainApp(hwnd, lParam);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED)
		{
			switch (LOWORD(wParam))
			{
			case BUTTON_SEND_MESSGES:
				handleButtonSend();
				break;
			case BUTTON_BROWSE_FILE:
				handleButtonBrowse();
				break;
			}
			//InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
void handleButtonLogin()
{
	userAccount = getText(hwTextboxAccount);
	userPassword = getText(hwTextboxPassword);

	//HashWinAPI hash;
	//hash.hash(userPassword.c_str(), userPassword.length());
	//userPassword = hash.getHash();
	//MessageBox(NULL, userPassword.c_str(), NULL, NULL);
	loginSuccess = true;
	DestroyWindow(hwndLogin);

}

void createWindowLogin(HWND hwnd, LPARAM lParam)
{
	hwLabelAccount = CreateWindowA("STATIC", "Account:", WS_CHILD | WS_VISIBLE | SS_LEFT, ALIGN, 10, 60, WIDTH_UNIT, hwnd, (HMENU)LABEL_ACCOUNT, hInstance, NULL);
	hwTextboxAccount = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN, 35, WIDTH_LOGIN - ALIGN * ALIGN_R, WIDTH_UNIT, hwnd, (HMENU)LABEL_ACCOUNT, hInstance, NULL);

	hwLabelPassword = CreateWindowA("STATIC", "Password:", WS_CHILD | WS_VISIBLE | SS_LEFT, ALIGN, 60, 90, WIDTH_UNIT, hwnd, (HMENU)LABEL_PASSWORD, hInstance, NULL);
	hwTextboxPassword = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | SS_CENTER | ES_PASSWORD, ALIGN, 85, WIDTH_LOGIN - ALIGN * ALIGN_R, WIDTH_UNIT, hwnd, (HMENU)LABEL_PASSWORD, hInstance, NULL);

	hwLabelResult = CreateWindowA("STATIC", "...", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN, 110, WIDTH_LOGIN - ALIGN * ALIGN_R, WIDTH_UNIT, hwnd, (HMENU)LABLE_RESULT, hInstance, NULL);
	hwButtonLogin = CreateWindowA("BUTTON", "Login", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN, 135, WIDTH_LOGIN - ALIGN * ALIGN_R, WIDTH_UNIT + 7, hwnd, (HMENU)BUTTON_LOGIN, hInstance, NULL);

}

void createWindowMainApp(HWND hwnd, LPARAM lParam)
{
	int row = 0;
	hwndLabelUserName = CreateWindowA("STATIC", "User name", WS_CHILD | WS_VISIBLE | SS_LEFT, ALIGN, 10 + row * DISTANCE_UNIT, 200, WIDTH_UNIT, hwnd, (HMENU)LABEL_USER_NAME, hInstance, NULL);

	hwndLabelChooseFriend = CreateWindowA("STATIC", "Choose friend:", WS_CHILD | WS_VISIBLE | SS_LEFT, 300, 13 + row * DISTANCE_UNIT, 95, WIDTH_UNIT, hwnd, (HMENU)LABEL_CHOOSE_FRIEND, hInstance, NULL);
	hwndComboboxChooseFriend = CreateWindowA(WC_COMBOBOX, "", CBS_SORT | WS_VSCROLL | CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | SS_LEFT, 410, 10 + row * DISTANCE_UNIT, 375, WIDTH_UNIT * 7, hwnd, (HMENU)COMBOBOX_CHOOSE_FRIEND, hInstance, NULL);
	for (int i = 0; i < 10; ++i)
	{
		char v[] = "No  ";
		v[3] = i + 48;
		SendMessage(hwndComboboxChooseFriend, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)v);
	}
	SendMessage(hwndComboboxChooseFriend, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

	hwndButtonChooseFriend = CreateWindowA("BUTTON", "Choose", WS_CHILD | WS_VISIBLE | SS_CENTER, 800, 10 + row * DISTANCE_UNIT, 80, WIDTH_UNIT + 4, hwnd, (HMENU)BUTTON_CHOOSE_FRIEND, hInstance, NULL);

	++row;
	hwndLabelFriend = CreateWindowA("STATIC", "Friend", WS_CHILD | WS_VISIBLE | SS_LEFT, ALIGN, 10 + row * DISTANCE_UNIT, 200, WIDTH_UNIT, hwnd, (HMENU)LABEL_USER_NAME, hInstance, NULL);

	hwndLabelStatusFriend = CreateWindowA("STATIC", "||...", WS_CHILD | WS_VISIBLE | SS_LEFT, 410, 10 + row * DISTANCE_UNIT, 375, WIDTH_UNIT, hwnd, (HMENU)LABEL_STATUS_FRIEND, hInstance, NULL);

	++row;

	hwndLabelDowloadFile = CreateWindowA("STATIC", "Download: ", WS_CHILD | WS_VISIBLE | SS_LEFT, 300, 13 + row * DISTANCE_UNIT, 95, WIDTH_UNIT, hwnd, (HMENU)LABEL_DOWLOAD_FILE, hInstance, NULL);
	hwndTextboxDowloadFile = CreateWindowA("EDIT", "", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER | ES_AUTOHSCROLL, 410, 10 + row * DISTANCE_UNIT, 700, WIDTH_UNIT + 4, hwnd, (HMENU)TEXTBOX_DOWNLOAD_FILE, hInstance, NULL);
	hwndButtonDowloadFile = CreateWindowA("BUTTON", "Download", WS_CHILD | WS_VISIBLE | SS_CENTER, 1130, 10 + row * DISTANCE_UNIT, 100, WIDTH_UNIT + 4, hwnd, (HMENU)BUTTON_DOWNLOAD_FILE, hInstance, NULL);

	++row;

	hwndLabelStatusDownload = CreateWindowA("STATIC", "||...", WS_CHILD | WS_VISIBLE | SS_LEFT, 410, 10 + row * DISTANCE_UNIT, 700, WIDTH_UNIT, hwnd, (HMENU)LABEL_STATUS_FRIEND, hInstance, NULL);

	++row;

	hwndLabelReceive = CreateWindowA("STATIC", "RECEIVE", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN, 10 + row * DISTANCE_UNIT, 600, WIDTH_UNIT, hwnd, (HMENU)LABEL_RECEIVE, hInstance, NULL);
	hwndLabelSend = CreateWindowA("STATIC", "SEND", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN * 2 + 650, 10 + row * DISTANCE_UNIT, 600, WIDTH_UNIT, hwnd, (HMENU)LABEL_SEND, hInstance, NULL);

	++row;

	hwndTextboxReceive = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_READONLY | ES_MULTILINE | ES_LEFT | ES_AUTOHSCROLL | ES_AUTOVSCROLL, ALIGN, 10 + row * DISTANCE_UNIT, 650, 600, hwnd, (HMENU)TEXTBOX_RECEIVE, hInstance, NULL);
	hwndTextboxSend = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_READONLY | ES_MULTILINE | ES_LEFT | ES_AUTOHSCROLL | ES_AUTOVSCROLL, ALIGN * 2 + 650, 10 + row * DISTANCE_UNIT, 650, 600, hwnd, (HMENU)TEXTBOX_SEND, hInstance, NULL);

	row += 17;

	hwndTextboxInputMessges = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_LEFT | ES_AUTOHSCROLL | ES_AUTOVSCROLL, ALIGN, 20 + row * DISTANCE_UNIT, 1200, 100, hwnd, (HMENU)TEXTBOX_INPUT_MESSGES, hInstance, NULL);
	hwndButtonSendMessges = CreateWindowA("BUTTON", "Send", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN * 2 + 1200 - 10, 20 + row * DISTANCE_UNIT, 90, WIDTH_UNIT + 4, hwnd, (HMENU)BUTTON_SEND_MESSGES, hInstance, NULL);

	++row;

	hwndButtonSendMessges = CreateWindowA("BUTTON", "Browse", WS_CHILD | WS_VISIBLE | SS_CENTER, ALIGN * 2 + 1200 - 10, 20 + row * DISTANCE_UNIT, 90, WIDTH_UNIT + 4, hwnd, (HMENU)BUTTON_BROWSE_FILE, hInstance, NULL);

	row += 2;

	hwndLabelStatusSend = CreateWindowA("STATIC", "Send: 100%", WS_CHILD | WS_VISIBLE | SS_LEFT, ALIGN, 20 + row * DISTANCE_UNIT, 90, WIDTH_UNIT, hwnd, (HMENU)LABLE_STATUS_SEND, hInstance, NULL);

}

void handleButtonSend()
{
	std::wstring text = getTextW(hwndTextboxInputMessges);
	addTextSend(text);
}

void handleButtonBrowse()
{
	OPENFILENAMEW ofn;
	WCHAR szFileName[MAX_PATH] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndApp;
	ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileNameW(&ofn))
	{
		std::wstring fileName = getFileNameW(ofn.lpstrFile);
		addTextSend(fileName);
	}

}

void addTextSend(const std::wstring& text)
{
	messgesSend += text + L"\r\n";
	setTextW(hwndTextboxSend, messgesSend);
	setTextW(hwndTextboxInputMessges, L"");
}


bool setTextW(HWND hwnd, const std::wstring& text)
{
	SetWindowTextW(hwnd, text.c_str());
	return true;
}

std::wstring getTextW(HWND hwnd)
{
	int textSize = GetWindowTextLengthW(hwnd) + 1;
	WCHAR text[MAX_LENGTH_TEXT];
	//std::wstring text(textSize+23,'0');
	if (textSize < 1)
	{
		return L"";
	}

	//GetWindowTextW(hwnd, (LPWSTR) (text.c_str()), textSize);
	GetWindowTextW(hwnd, text, textSize);
	return text;
}

std::string getText(HWND hwnd)
{
	int textSize = GetWindowTextLengthA(hwnd) + 1;
	CHAR text[MAX_LENGTH_TEXT];
	if (textSize < 1)
	{
		return "";
	}
	GetWindowTextA(hwnd, text, textSize);
	return text;
}

std::wstring getFileNameW(const std::wstring& path)
{
	return path.substr(path.find_last_of(L"/\\") + 1);
}