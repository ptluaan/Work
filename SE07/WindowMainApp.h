
#ifndef WINDOWMAIAPP_H
#define WINDOWMAIAPP_H

#define WIDTH_MAIN_APP  1375
#define HEIGHT_MAIN_APP 960
enum HMain
{
	LABEL_USER_NAME = 1,
	LABEL_FRIEND,
	LABEL_CHOOSE_FRIEND,
	COMBOBOX_CHOOSE_FRIEND,
	BUTTON_CHOOSE_FRIEND,
	LABEL_STATUS_FRIEND,
	LABEL_DOWLOAD_FILE,
	TEXTBOX_DOWNLOAD_FILE,
	BUTTON_DOWNLOAD_FILE,
	LABEL_STATUS_DOWLOAD,
	LABEL_RECEIVE,
	TEXTBOX_RECEIVE,
	LABEL_SEND,
	TEXTBOX_SEND,
	LABEL_INPUT_MESSEGES,
	TEXTBOX_INPUT_MESSGES,
	BUTTON_SEND_MESSGES,
	BUTTON_BROWSE_FILE,
	LABLE_STATUS_SEND
};

HWND hwndApp;
HWND hwndLabelUserName, hwndLabelFriend;
HWND hwndLabelChooseFriend, hwndComboboxChooseFriend, hwndButtonChooseFriend, hwndLabelStatusFriend;
HWND hwndLabelDowloadFile, hwndTextboxDowloadFile, hwndButtonDowloadFile, hwndLabelStatusDownload;
HWND hwndLabelReceive, hwndTextboxReceive;
HWND hwndLabelSend, hwndTextboxSend;
HWND hwndLabelInputMessges, hwndTextboxInputMessges, hwndButtonSendMessges, hwndButtonBrowseFile, hwndLabelStatusSend;

std::wstring messgesSend, messgesReceive;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void createWindowMainApp(HWND, LPARAM);
void doApp();
void handleButtonSend();
void handleButtonBrowse();
void addTextSend(const std::wstring& text);
bool setTextW(HWND hwnd, const std::wstring& text);
std::wstring getTextW(HWND hwnd);
std::string getText(HWND hwnd);

#endif // !WINDOWMAIAPP_H
