#include <windows.h>
#include "hook.h"

void ShowMessage(const std::string &message);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
    try {
        auto hook_dll = hook::load("gettext.dll");
        hook_dll->initialize();
        ShowMessage("Press Ok for exit");
    }
    catch (std::exception &e) {
        ShowMessage(e.what());
    }

    return 0;
}

void ShowMessage(const std::string &message) {
    MessageBoxA(NULL, message.c_str(), "Get Password tool", MB_ICONINFORMATION);
}