#pragma once

#include <Core/IXtPlatform.h>

namespace xt {
namespace platform {
    class XtDefaultDevice : public xt::IXtPlatform {
    public:
        bool createDevice(int width, int height, bool fullscreen, bool reinit) override;
        void onDeviceUpdate() override;
        void onResize(int width, int height) override;
    };
}
}