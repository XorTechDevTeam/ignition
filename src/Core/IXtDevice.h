/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
    class IXtDevice {
    protected:
        vec2 _screenSize;
        render::IXtRenderDevice* _renderDevice = nullptr;
    public:
        IXtDevice() =  default;
        virtual ~IXtDevice() {
            if (_renderDevice) {
                delete _renderDevice;
                _renderDevice = nullptr;
            }
        }

        virtual bool createDevice() = 0;
        virtual void onDeviceUpdate(float delta) = 0;
        virtual bool isDeviceActive() = 0;
        virtual void onScroll(double xOffset, double yOffset) = 0;
        virtual void onKeyboard(int key, int action, int mods) = 0;
        virtual void onTouch(const Vector<vec2>& touches) = 0;
        virtual void onResize(int width, int height) = 0;
    };
}