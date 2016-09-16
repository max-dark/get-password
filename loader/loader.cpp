#include <windows.h>
#include "hook.h"

void ShowMessage(const std::string &message);

void OutError() {
    LPVOID lpMsgBuf;
    DWORD err = GetLastError();
    if (!err) return;
    FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            err,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR) &lpMsgBuf,
            0, NULL);
    MessageBoxW(NULL, (LPWSTR) lpMsgBuf, L"Error", MB_ICONINFORMATION);
    LocalFree(lpMsgBuf);
    SetLastError(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
    try {
        auto item = hook::setup("gettext.dll");
        ShowMessage("Press Ok for exit");
    }
    catch (std::exception &e) {
        ShowMessage(e.what());
    }

    return 0;
}

void ShowMessage(const std::string &message) {
    MessageBoxA(NULL, message.c_str(), "Get Text", MB_ICONINFORMATION);
}