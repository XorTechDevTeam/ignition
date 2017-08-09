//
// Created by droncode on 8/9/17.
//

#pragma once

namespace xt {
    namespace render {
        class IXtRenderDevice {
        protected:
            bool _fullscreen;
            int _width;
            int _height;
        public:
            IXtRenderDevice(int width, int height, bool fullscreen = false) : _width(width),
                                                                              _height(height),
                                                                              _fullscreen(fullscreen) {}

            virtual ~IXtRenderDevice() = default;
            virtual void drawFrame(float delta) = 0;

            void setFullscreen(bool value) { _fullscreen = value; }
            bool isFullscreen() const { return _fullscreen; }
            void getScreenResolution(int& width, int& height) const { width = _width; height = _height; }
            virtual void setScreenResolution(int width, int height) { _width = width; _height = height; }

            //Here we will be compile shaders, register textures and other stf
        };
    }
}