/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Input/XtInputCommon.h>
#include <Core/Input/IXtInputObserver.h>

namespace xt {
namespace input {
    class XtInputManager {
    private:
        Vector<IXtInputObserver*> _observers;
    public:
        XtInputManager() = default;
        ~XtInputManager();

        void registerInputObserver(IXtInputObserver* observer);
        void unRegisterInputObserver(IXtInputObserver* observer);

        void onKeyboardKey(const KeyboardEvent& keyboardEvent);
        void onTouch(const Vector<TapInfo>& points);
        void onScroll(double x, double y);
    };
}
}


