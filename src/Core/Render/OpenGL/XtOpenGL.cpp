#include "XtOpenGL.h"

namespace xt {
namespace render {
    bool XtOpenGL::init() {
        glViewport(0, 0, _width, _height);
        LOGMSG("*** Init render (%d;%d) ***", _width, _height);

        return true;
    }

    void XtOpenGL::changeViewport(int width, int height) {
        _width = width;
        _height = height;
        glViewport(0, 0, _width, _height);
    }

    void XtOpenGL::drawFrame(float delta) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 1.f, 1.0f);
        //TODO: Draw frame
    }

    bool XtOpenGL::reInit() {
        //TODO: Reload all textures, shaders and other staff
        return true;
    }
}
}