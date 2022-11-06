#ifndef WINDOWLOGIN_H
#define WINDOWLOGIN_H

#define WIDTH_LOGIN  400
#define HEIGHT_LOGIN 230


#define MAX_LENGTH_TEXT 1024
enum HLogin
{
	LABEL_ACCOUNT = 1,
	TEXTBOX_ACCOUNT,
	LABEL_PASSWORD,
	TEXTBOX_PASSWORD,
	BUTTON_LOGIN,
	LABLE_RESULT,
};

HWND hwndLogin;

HWND hwLabelAccount, hwTextboxAccount;
HWND hwLabelPassword, hwTextboxPassword;
HWND hwButtonLogin;
HWND hwLabelResult;

bool loginSuccess = false;
std::string userAccount;
std::string userPassword;

LRESULT CALLBACK WndProcLogin(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void createWindowLogin(HWND hwnd, LPARAM lParam);
bool loginApp();
void handleButtonLogin();
std::string getText(HWND hwnd);

#endif // !WINDOWLOGIN_H
