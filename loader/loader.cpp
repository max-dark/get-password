#include <Windows.h>

typedef void(*proc)(HINSTANCE xmod);
bool hooked = false;
HMODULE lib = 0;     // истанс библиотеки перехвата
proc Init = NULL;    // указатель на инициализацию перехватчика
proc Release = NULL; // свобождение перехватчика

void OutError() {
	LPVOID lpMsgBuf;
	DWORD err = GetLastError();
	if (!err) return;
	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf,
		0, NULL);
	MessageBoxW(NULL, (LPWSTR)lpMsgBuf, L"Error", MB_ICONINFORMATION);
	LocalFree(lpMsgBuf);
	SetLastError(0);
}


void Hook(HWND parent) {
	static const WCHAR modpath[] = L"gettext.dll";
	if (!hooked) {
		lib = LoadLibraryW(modpath);
		if (!lib) goto eExit;
		Init = (proc)GetProcAddress(lib, "Init");
		if (!Init) goto eQuit;
		Release = (proc)GetProcAddress(lib, "Release");
		if (!Release) goto eQuit;
		Init(lib);
		hooked = true;
	}
	return;
eQuit:
	FreeLibrary(lib);
	Init = NULL;
	Release = NULL;
	hooked = false;
eExit:
	MessageBeep(MB_ICONEXCLAMATION);
	OutError();
}


void UnHook() {
	if (hooked) {
		Release(lib);
		FreeLibrary(lib);
		Init = NULL;
		Release = NULL;
		hooked = false;
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd) {
	Hook(NULL);
	if (hooked) {
		MessageBoxW(NULL, L"Press Ok for exit", L"Get Text", MB_ICONINFORMATION);
	}
	UnHook();
	return 0;
}