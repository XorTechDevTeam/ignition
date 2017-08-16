#pragma once

#include <string>
#include <Windows.h>

namespace xt {
namespace platform {
	class XtWindowInstance {
	private:
		HWND _handle;
	public:
		~XtWindowInstance();

		bool createWindow(const std::string& title, int width, int height);
		void update();
	};
}
}