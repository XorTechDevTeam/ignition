/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
    class IXtPlatform {
    protected:
    public:
        IXtPlatform() =  default;
        virtual ~IXtPlatform() = default;

        virtual bool createDevice(int width, int height, bool fullscreen, bool reinit) = 0;
        virtual void onDeviceUpdate() = 0;
        virtual bool isTerminate() const = 0;
        virtual void onResize(int width, int height) = 0;
    };
}