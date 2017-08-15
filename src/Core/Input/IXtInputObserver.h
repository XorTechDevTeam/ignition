/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Input/XtInputCommon.h>

namespace xt {
namespace input {
    /**
     * @brief Слушатель событий из системы ввода. Пока что 3 основных источника - мышь, клава, тач
     */
    class IXtInputObserver {
    public:
        /**
         * @brief Получено событие от клавиатуры (клавиша и ее конфиг)
         * @param keyboardEvent - описание события
         */
        virtual void onKeyboardEvent(const KeyboardEvent& keyboardEvent) {}
        /**
         * @brief Получено событие тача (или мультитача)
         * @param tapVector - вектор точек нажатия
         */
        virtual void onTouchEvent(const Vector<TapInfo>& tapVector) {}
        /**
         * @brief События скролла
         * @param x - дельта по X
         * @param y - дельта по Y
         */
        virtual void onScrollEvent(double x, double y) {}
    };
}
}