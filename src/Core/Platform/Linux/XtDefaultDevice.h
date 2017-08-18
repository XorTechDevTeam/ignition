#pragma once

#include <Core/IXtPlatform.h>

namespace xt {
namespace platform {
    class XtDefaultDevice : public xt::IXtPlatform {
    private:
        GLFWwindow* _window;
    public:
        ~XtDefaultDevice() override;

        bool createDevice(int width, int height, bool fullscreen, bool reinit) override;
        void onDeviceUpdate() override;
        bool isTerminate() const override;
        void onResize(int width, int height) override;
        /**
         * GLFW Callbacks
         */
        static void glfwOnKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void glfwOnMouseInput(GLFWwindow* window, int button, int action, int mods);
        static void glfwOnWindowResize(GLFWwindow* window, int width, int height);
        static void glfwOnScroll(GLFWwindow* window, double xoffset, double yoffset);
        static void glfwCloseApplication(GLFWwindow* window);
    };
}
}