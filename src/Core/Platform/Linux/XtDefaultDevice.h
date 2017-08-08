#pragma once

#include <Core/IXtDevice.h>

namespace xt {
namespace platform {
    class XtDefaultDevice : public xt::IXtDevice {
    private:
        GLFWwindow* _window;
    public:
        ~XtDefaultDevice() override;

        bool createDevice() override;
        void onDeviceUpdate(float delta) override;
        bool isDeviceActive() override;
        void onScroll(double xOffset, double yOffset) override;
        void onKeyboard(int key, int action, int mods) override;
        void onTouch(const Vector<vec2>& touches) override;
        void onResize(int width, int height) override;
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