//
// Created by droncode on 8/12/17.
//

#include "XtDefaultDevice.h"
#include <Core/Render/OpenGL/XtOpenGL.h>
#include <Core/XtEngine.h>

namespace xt {
namespace platform {
    bool XtDefaultDevice::createDevice(int width, int height, bool fullscreen, bool reinit) {
        if (!reinit) {
            _renderDevice = new render::XtOpenGL(width, height);
        }
        return true;
    }

    void XtDefaultDevice::onDeviceUpdate() {

    }

    bool XtDefaultDevice::isTerminate() const {
        return false;
    }

    void XtDefaultDevice::onResize(int width, int height) {

    }
}
}