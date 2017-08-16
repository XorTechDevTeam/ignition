#include "XtWindowInstance.h"
#include <XtCommon.h>
#include <Core/XtEngine.h>

#define XT_WIN32CLASSID "XorTechWin32ApplicationClass"
#define XT_WIN32CLASSEX (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

LRESULT CALLBACK XtWin32EventProcessCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		xt::XtEngine::getInstance()->offline();
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace xt {
namespace platform {
	XtWindowInstance::~XtWindowInstance() {
		UnregisterClass(XT_PROJECT_NAME, xt::win32::g_win32AppInstance);
	}

	bool XtWindowInstance::createWindow(const std::string& title, int width, int height) {
		WNDCLASSEX winClass;

		winClass.cbSize = sizeof(WNDCLASSEX);
		winClass.style = CS_HREDRAW | CS_VREDRAW;
		winClass.lpfnWndProc = XtWin32EventProcessCallback;
		winClass.cbClsExtra = 0;
		winClass.cbWndExtra = 0;
		winClass.hInstance = xt::win32::g_win32AppInstance;
		winClass.hIcon = LoadIcon(xt::win32::g_win32AppInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		winClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		winClass.lpszMenuName = NULL;
		winClass.lpszClassName = XT_WIN32CLASSID;
		winClass.hIconSm = LoadIcon(winClass.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

		if (!RegisterClassEx(&winClass)) {
			LOGMSG("ERROR: Unable to register window class");
			return false;
		}

		_handle = CreateWindow(XT_WIN32CLASSID,
			title.c_str(), 
			XT_WIN32CLASSEX, 
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			width, 
			height, 
			nullptr, 
			nullptr, 
			xt::win32::g_win32AppInstance, 
			nullptr);

		if (!_handle) {
			LOGMSG("ERROR: Unable to create window class. Win32Errno = 0x%X", GetLastError());
			return false;
		}

		return true;
	}

	void XtWindowInstance::update() {
		ShowWindow(_handle, SW_SHOW);
		UpdateWindow(_handle);

		MSG eventMessage;
		if (GetMessage(&eventMessage, _handle, 0, 0)) {
			TranslateMessage(&eventMessage);
			DispatchMessage(&eventMessage);
		}
	}
}
}