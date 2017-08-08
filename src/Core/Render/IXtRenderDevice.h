//
// Created by droncode on 8/9/17.
//

#pragma once

namespace xt {
    namespace render {
        class IXtRenderDevice {
        public:
            virtual ~IXtRenderDevice() = default;
            virtual void drawFrame(float delta) = 0;
            //Here we will be compile shaders, register textures and other stf
        };
    }
}