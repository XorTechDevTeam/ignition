/**
 * XorTech Source Code
 */
#include "XtInputManager.h"

namespace xt {
namespace input {
    XtInputManager::~XtInputManager() {
        for (auto& it : _observers) {
            delete it;
            it = nullptr;
        }
        _observers.clear();
    }

    void XtInputManager::registerInputObserver(IXtInputObserver *observer) {
        _observers.emplace_back(observer);
    }

    void XtInputManager::unRegisterInputObserver(IXtInputObserver *observer) {
        _observers.erase(std::find(_observers.begin(), _observers.end(), observer));
    }

    void XtInputManager::onKeyboardKey(const KeyboardEvent &keyboardEvent) {
        for (auto& it : _observers) {
            it->onKeyboardEvent(keyboardEvent);
        }
    }

    void XtInputManager::onTouch(const Vector<TapInfo> &points) {
        for (auto& it : _observers) {
            it->onTouchEvent(points);
        }
    }

    void XtInputManager::onScroll(double x, double y) {
        for (auto& it : _observers) {
            it->onScrollEvent(x, y);
        }
    }
}
}