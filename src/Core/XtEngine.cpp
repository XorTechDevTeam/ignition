/**
 * XorTech Source Code
 */
#include "XtEngine.h"
#include <Core/Time/XtSystemTime.h>

#if defined(XT_LINUX)
#include <Core/Platform/Linux/XtDefaultDevice.h>
#endif

namespace xt {
    XtEngine::~XtEngine() {
        if (_platform != nullptr) {
            delete _platform;
            _platform = nullptr;
        }
        if (_inputManager != nullptr) {
            delete _inputManager;
            _inputManager = nullptr;
        }
        if (_systemTime != nullptr) {
            delete _systemTime;
            _systemTime = nullptr;
        }
    }

    bool XtEngine::init(const XtDeviceParams &deviceParams) {
        _initParams = deviceParams;
        _platform = new xt::platform::XtDefaultDevice();
        _inputManager = new xt::input::XtInputManager();
        _systemTime = new xt::time::XtSystemTime();
        _gameTime = nullptr;    //TODO: Create class for game time

        if (!_platform->createDevice(_initParams.width, _initParams.height, _initParams.fullscreen, false)) {
            //TODO: Log about it
            return false;
        }

        _renderDevice = _platform->getRenderDevice();

        return true;
    }

    int XtEngine::run() {
        double time = _systemTime->getTime();

        while (!_platform->isTerminate()) {
            const double newTime = _systemTime->getTime();
            const float delta  = static_cast<float>(newTime - time);

            time = newTime;

            if (_gameTime != nullptr) {
                _gameTime->update();
            }

            _platform->onDeviceUpdate();
            _renderDevice->drawFrame(delta);
        }
        return 0;
    }
}