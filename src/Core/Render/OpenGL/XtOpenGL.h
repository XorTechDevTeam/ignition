#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
namespace render {
    class XtOpenGL : public IXtRenderDevice {
    public:
        XtOpenGL(int width, int height, bool fullscreen = false) : IXtRenderDevice(width, height, fullscreen) {}

        void drawFrame(float delta) override;
    };
}
}


