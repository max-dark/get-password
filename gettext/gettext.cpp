#include <Windows.h>

#pragma comment(linker,"/entry:DllMain")

#define XHOOK_API __declspec(dllexport)

extern "C"
{
XHOOK_API void Release(HINSTANCE xmod);
XHOOK_API void Init(HINSTANCE xmod);
};

HINSTANCE xmod;
HHOOK xhook;


void GetStaredText(HWND wnd) {
    int len = GetWindowTextLengthW(wnd);
    WCHAR *buff = new WCHAR[len + 1];
    GetWindowTextW(wnd, buff, len + 1);
    MessageBoxW(NULL, buff, L"", MB_ICONINFORMATION);
    delete[] buff;
}

bool FilterMessage(PMSG msg) {
    bool result = false;
    if (msg->message == WM_MOUSEWHEEL) {
        GetStaredText(GetFocus());
    }
    return result;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    PMSG msg = (PMSG) lParam;
    switch (nCode) {
        case HC_ACTION:
            if (FilterMessage(msg))
                return 0;
            break;
        default:
            break;
    }
    return CallNextHookEx(xhook, nCode, wParam, lParam);
}


void OutError() {
    LPVOID lpMsgBuf;
    DWORD err = GetLastError();
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

BOOL WINAPI DllMain(HINSTANCE dll_instance, DWORD fdwReason, LPVOID) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        xmod = dll_instance;
        xhook = 0;
        if (!xmod)
            OutError();
    }
    return TRUE;
}

XHOOK_API void Release(HINSTANCE) {
    UnhookWindowsHookEx(xhook);
}

XHOOK_API void Init(HINSTANCE xmod) {
    xhook = SetWindowsHookExW(WH_GETMESSAGE, HookProc, xmod, 0);
    if (!xhook) {
        OutError();
        MessageBeep(IDOK);
    }
}
