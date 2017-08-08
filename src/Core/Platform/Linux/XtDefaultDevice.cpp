#include "XtDefaultDevice.h"
#include <Core/Render/OpenGL/XtOpenGL.h>
#include <Core/XtEngine.h>

namespace xt {
    namespace platform {
        XtDefaultDevice::~XtDefaultDevice() {
            glfwTerminate();
        }

        bool XtDefaultDevice::createDevice() {
            if (!glfwInit()) {
                //TODO: log here
                return false;
            }

            /**
             * OpenGL 3.3
             */
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            _window = glfwCreateWindow(XT_SCREEN_MIN_WIDTH, XT_SCREEN_MIN_HEIGHT, XT_PROJECT_NAME, nullptr, nullptr);
            if (!_window)
            {
                glfwTerminate();
                //TODO: log error
                return false;
            }

            glfwMakeContextCurrent(_window);

            _renderDevice = new render::XtOpenGL();

            glfwSetKeyCallback(_window, &XtDefaultDevice::glfwOnKeyboardEvent);
            glfwSetMouseButtonCallback(_window, &XtDefaultDevice::glfwOnMouseInput);
            glfwSetWindowSizeCallback(_window, &XtDefaultDevice::glfwOnWindowResize);
            glfwSetScrollCallback(_window, &XtDefaultDevice::glfwOnScroll);

            return true;
        }

        void XtDefaultDevice::onDeviceUpdate(float delta) {
            _renderDevice->drawFrame(delta);
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }

        bool XtDefaultDevice::isDeviceActive() {
            return !static_cast<bool>(glfwWindowShouldClose(_window));
        }

        void XtDefaultDevice::onScroll(double xOffset, double yOffset) {
            //TODO: Send event to input system
        }

        void XtDefaultDevice::onKeyboard(int key, int action, int mods) {
            //TODO: Send event to input system
        }

        void XtDefaultDevice::onTouch(const Vector<vec2> &touches) {
            //TODO: Send event to input system
        }

        void XtDefaultDevice::onResize(int width, int height) {
            //TODO: Send event to input system
        }

        /**
         * GLFW Callbacks
         */

        void XtDefaultDevice::glfwOnKeyboardEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
            xt::XtEngine::getInstance()->getCurrentDevice()->onKeyboard(key, action, mods);
        }

        void XtDefaultDevice::glfwOnMouseInput(GLFWwindow *window, int button, int action, int mods) {
            //TODO: Think about long taps and other combos
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                xt::XtEngine::getInstance()->getCurrentDevice()->onTouch({ vec2(x, y) });
            }
        }

        void XtDefaultDevice::glfwOnWindowResize(GLFWwindow *window, int width, int height) {
            xt::XtEngine::getInstance()->getCurrentDevice()->onResize(width, height);
        }

        void XtDefaultDevice::glfwOnScroll(GLFWwindow *window, double xoffset, double yoffset) {
            xt::XtEngine::getInstance()->getCurrentDevice()->onScroll(xoffset, yoffset);
        }
    }
}