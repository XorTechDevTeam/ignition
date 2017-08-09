/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
    class IXtDevice {
    protected:
        render::IXtRenderDevice* _renderDevice = nullptr;
    public:
        IXtDevice() =  default;
        virtual ~IXtDevice() {
            if (_renderDevice) {
                delete _renderDevice;
                _renderDevice = nullptr;
            }
        }

        virtual bool createDevice(int width = XT_SCREEN_MIN_WIDTH, int height = XT_SCREEN_MIN_HEIGHT, bool fullscreen = false, bool reinit = false) = 0;
        virtual void onDeviceUpdate(float delta) = 0;
        virtual bool isDeviceActive() = 0;
        virtual void onResize(int width, int height) = 0;
        virtual void switchFullscreenMode(bool mode) {}

        render::IXtRenderDevice* getRenderDevice() { return _renderDevice; }
    };
}