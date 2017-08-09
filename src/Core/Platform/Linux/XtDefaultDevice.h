#pragma once

#include <Core/IXtDevice.h>

namespace xt {
namespace platform {
    class XtDefaultDevice : public xt::IXtDevice {
    private:
        GLFWwindow* _window;
    public:
        ~XtDefaultDevice() override;

        bool createDevice(int width = XT_SCREEN_MIN_WIDTH, int height = XT_SCREEN_MIN_HEIGHT, bool fullscreen = false, bool reinit = false) override;
        void onDeviceUpdate(float delta) override;
        bool isDeviceActive() override;
        void onResize(int width, int height) override;
        void switchFullscreenMode(bool mode) override;
        /**
         * GLFW Callbacks
         */
        static void glfwOnKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwOnMouseInput(GLFWwindow* window, int button, int action, int mods);
        static void glfwOnWindowResize(GLFWwindow* window, int width, int height);
        static void glfwOnScroll(GLFWwindow* window, double xoffset, double yoffset);
    };
}
}