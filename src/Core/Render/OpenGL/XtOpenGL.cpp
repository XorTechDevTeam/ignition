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
        glClearColor(1.f, 0.f, 0.f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }
}
}