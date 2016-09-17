#include <Windows.h>

#pragma comment(linker,"/entry:DllMain")

#define HOOK_LIB_API __declspec(dllexport)

extern "C"
{
HOOK_LIB_API void Release(HINSTANCE);
HOOK_LIB_API void Init(HINSTANCE);
};

static HINSTANCE lib_instance = nullptr;
static HHOOK hook_handle = nullptr;


void GetStaredText(HWND wnd) {
    int len = GetWindowTextLengthW(wnd);
    WCHAR *buff = new WCHAR[len + 1];
    GetWindowTextW(wnd, buff, len + 1);
    MessageBoxW(NULL, buff, L"press [ctrl+c] to copy text : Get Password tool", MB_ICONINFORMATION);
    delete[] buff;
}

bool FilterMessage(PMSG msg) {
    bool result = false;
    if (msg->message == WM_MOUSEWHEEL) {
        GetStaredText(GetFocus());
    }
    return result;
}

LRESULT CALLBACK hook_function(int nCode, WPARAM wParam, LPARAM lParam) {
    PMSG msg = (PMSG) lParam;
    switch (nCode) {
        case HC_ACTION:
            if (FilterMessage(msg))
                return 0;
            break;
        default:
            break;
    }
    return CallNextHookEx(hook_handle, nCode, wParam, lParam);
}


void ShowLastError() {
    LPVOID lpMsgBuf;
    DWORD err = GetLastError();
    FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            err,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR) &lpMsgBuf,
            0, NULL);
    MessageBoxW(NULL, (LPWSTR) lpMsgBuf, L"Error is happened : Get Password tool", MB_ICONINFORMATION);
    LocalFree(lpMsgBuf);
    SetLastError(0);
}

BOOL WINAPI DllMain(HINSTANCE dll_instance, DWORD fdwReason, LPVOID) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        lib_instance = dll_instance;
        hook_handle = nullptr;
        if (!lib_instance)
            ShowLastError();
    }
    return TRUE;
}

HOOK_LIB_API void Release(HINSTANCE) {
    UnhookWindowsHookEx(hook_handle);
    hook_handle = nullptr;
}

HOOK_LIB_API void Init(HINSTANCE lib) {
    hook_handle = SetWindowsHookExW(WH_GETMESSAGE, hook_function, lib, 0);
    if (!hook_handle) {
        ShowLastError();
        MessageBeep(IDOK);
    }
}
