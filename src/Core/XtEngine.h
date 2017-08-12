/**
 * XorTech Source Code
 */
#pragma once

#include <Core/Render/IXtRenderDevice.h>
#include <Core/Input/XtInputManager.h>
#include <Core/IXtPlatform.h>
#include <Core/IXtTime.h>
#include <Core/XtDeviceParams.h>
#include <XtCommon.h>

namespace xt {
    using namespace input;
    using namespace render;

    class XtEngine : public patterns::XtSingleton<XtEngine> {
    private:
        IXtPlatform*     _platform;
        XtDeviceParams   _initParams;
        XtInputManager*  _inputManager;
        IXtRenderDevice* _renderDevice;

        IXtTime*        _systemTime;
        IXtTime*        _gameTime;
    public:
        ~XtEngine() override;

        bool init(const XtDeviceParams& deviceParams = XtDeviceParams());
        int run();

        IXtTime* getSystemTime() { return _systemTime; }
        IXtTime* getGameTime() { return _gameTime; }
        IXtPlatform* getCurrentPlatform() { return _platform; }
        XtInputManager* getInputManager() { return _inputManager; }
    };
}