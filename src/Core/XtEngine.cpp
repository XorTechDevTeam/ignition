/**
 * XorTech Source Code
 */
#include "XtEngine.h"
#include <Core/Time/XtSystemTime.h>
#include <Modules/XtModuleManager.h>

#if defined(XT_LINUX)
#include <Core/Platform/Linux/XtDefaultDevice.h>
#endif

namespace xt {
    XtEngine::XtEngine() : _platform(nullptr),
                           _initParams(XtDeviceParams()),
                           _inputManager(nullptr),
                           _renderDevice(nullptr),
                           _systemTime(nullptr),
                           _gameTime(nullptr),
                           _inLoop(true),
                           _isActive(true) {}

    XtEngine::~XtEngine() {
        if (_platform != nullptr) {
            delete _platform;
            _platform = nullptr;
        }
        if (_renderDevice) {
            delete _renderDevice;
            _renderDevice = nullptr;
        }
        if (_inputManager != nullptr) {
            delete _inputManager;
            _inputManager = nullptr;
        }
        if (_systemTime != nullptr) {
            delete _systemTime;
            _systemTime = nullptr;
        }

        xt::modules::XtModuleManager::release();
    }

    XtEngine* XtEngine::getInstance() {
        if (!_instance) {
            _instance = new XtEngine();
        }
        return _instance;
    }

    void XtEngine::release() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    bool XtEngine::init(const XtDeviceParams &deviceParams) {
        _initParams = deviceParams;
        _platform = new xt::platform::XtDefaultDevice();
        _inputManager = new xt::input::XtInputManager();
        _systemTime = new xt::time::XtSystemTime();
        _gameTime = nullptr;
        _lastFrameTime = _systemTime->getTime();

        if (!_platform->createDevice(_initParams.width, _initParams.height, _initParams.fullscreen, false)) {
            LOGMSG("Unable to create platform device!");
            return false;
        }

#if defined(XT_LINUX) || defined(XT_ANDROID) || defined(XT_IOS)
        _renderDevice = new xt::render::XtOpenGL(_initParams.width, _initParams.height);
#else
#error "DirectX render not supported yet"
#endif
        if (!_renderDevice->init()) {
            LOGMSG("Unable to init render device!");
            return false;
        }

        xt::modules::XtModuleManager::getInstance()->init();

        return true;
    }

    void XtEngine::update() {
        if (_isActive) {
            const double newTime = _systemTime->getTime();
            const float delta = static_cast<float>(newTime - _lastFrameTime);

            _lastFrameTime = newTime;

            if (_gameTime) {
                _gameTime->update();
            }

            _platform->onDeviceUpdate();
            _renderDevice->drawFrame(delta);
        }
    }

    bool XtEngine::isOnline() const {
        return _inLoop;
    }

    void XtEngine::offline() {
        _inLoop = false;
    }

    void XtEngine::pause() {
        _isActive = true;
    }

    void XtEngine::resume() {
        _isActive = true;
    }
}

xt::XtEngine* xt::XtEngine::_instance = nullptr;