#pragma once

#include <XtCommon.h>
#include <Core/Render/IXtRenderDevice.h>

namespace xt {
namespace render {
    class XtOpenGL : public IXtRenderDevice {
    public:
        void drawFrame(float delta) override;
    };
}
}


