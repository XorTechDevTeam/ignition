#include "XtDefaultDevice.h"
#include <Core/XtEngine.h>

namespace xt {
    namespace platform {
        XtDefaultDevice::~XtDefaultDevice() {
			if (_wndInstance) {
				delete _wndInstance;
				_wndInstance = nullptr;
			}
        }

        bool XtDefaultDevice::createDevice(int width, int height, bool fullscreen, bool reinit) {
			_wndInstance = new XtWindowInstance();

			return _wndInstance->createWindow(XT_PROJECT_NAME, width, height);
        }

        void XtDefaultDevice::onDeviceUpdate() {
			if (_wndInstance) {
				_wndInstance->update();
			}
        }

        void XtDefaultDevice::onResize(int width, int height) {
            LOGMSG("UI::Resize(%d;%d)", width, height);
        }
    }
}