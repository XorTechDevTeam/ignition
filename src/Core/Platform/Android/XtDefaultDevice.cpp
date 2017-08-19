//
// Created by droncode on 8/12/17.
//

#include "XtDefaultDevice.h"
#include <Core/Render/OpenGL/XtOpenGL.h>
#include <Core/XtEngine.h>

namespace xt {
namespace platform {
    bool XtDefaultDevice::createDevice(int width, int height, bool fullscreen, bool reinit) {
        return true;
    }

    void XtDefaultDevice::onDeviceUpdate() {
    }

    void XtDefaultDevice::onResize(int width, int height) {
        xt::XtEngine::getInstance()->getRenderDevice()->changeViewport(width, height);
    }
}
}