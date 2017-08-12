/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
    class IXtPlatform {
    protected:
        render::IXtRenderDevice* _renderDevice = nullptr;
    public:
        IXtPlatform() =  default;
        virtual ~IXtPlatform() {
            if (_renderDevice != nullptr) {
                delete _renderDevice;
                _renderDevice = nullptr;
            }
        }

        virtual bool createDevice(int width, int height, bool fullscreen, bool reinit) = 0;
        virtual void onDeviceUpdate() = 0;
        virtual bool isTerminate() const = 0;
        virtual void onResize(int width, int height) = 0;
        virtual void switchFullscreenMode(bool mode) {}

        render::IXtRenderDevice* getRenderDevice() { return _renderDevice; }
    };
}