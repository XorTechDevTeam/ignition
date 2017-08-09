/**
 * XorTech Source Code
 */
#include "XtEngine.h"

#if defined(XT_LINUX)
#include <Core/Platform/Linux/XtDefaultDevice.h>
#endif

namespace xt {
    XtEngine::XtEngine() {
        _device = new xt::platform::XtDefaultDevice();
        _inputManager = new xt::input::XtInputManager();
    }

    XtEngine::~XtEngine() {
        if (_device) {
            delete _device;
            _device = nullptr;
        }
        if (_inputManager) {
            delete _inputManager;
            _inputManager = nullptr;
        }
    }

    int XtEngine::run() {
        if (!_device->createDevice()) {
            //TODO: Log about it
            return -1;
        }

        double time = glfwGetTime();

        while (_device->isDeviceActive()) {
            double newTime = glfwGetTime();
            float dt = static_cast<float>(newTime - time);
            time = newTime;
            _device->onDeviceUpdate(dt);
        }

        return 0;
    }
}