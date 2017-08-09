/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Input/XtInputCommon.h>

namespace xt {
namespace input {
    class IXtInputObserver {
    public:
        virtual void onKeyboardEvent(const KeyboardEvent& keyboardEvent) {}
        virtual void onTouchEvent(const Vector<TapInfo>& tapVector) {}
        virtual void onScrollEvent(double x, double y) {}
    };
}
}