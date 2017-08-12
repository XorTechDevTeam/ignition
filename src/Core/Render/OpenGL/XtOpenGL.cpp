#include "XtOpenGL.h"

namespace xt {
namespace render {
    void XtOpenGL::drawFrame(float delta) {
        glClearColor(1.f, 0.f, 0.f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }
}
}