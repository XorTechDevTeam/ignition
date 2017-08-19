#pragma once

#include <Core/IXtPlatform.h>
#include <Core/Platform/Windows/XtWindowInstance.h>

namespace xt {
namespace platform {
    class XtDefaultDevice : public xt::IXtPlatform {
	private:
		XtWindowInstance *_wndInstance;
    public:
		XtDefaultDevice() : _wndInstance(nullptr) {}
        ~XtDefaultDevice() override;

        bool createDevice(int width, int height, bool fullscreen, bool reinit) override;
        void onDeviceUpdate() override;
        void onResize(int width, int height) override;

		XtWindowInstance* getCurrentWindow() { return _wndInstance; }
    };
}
}