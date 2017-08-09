/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>

namespace xt {
namespace input {
    struct TapInfo {
        enum TapType {
            TAP_DOWN,
            TAP_UP
        } tapType;

        double x;
        double y;
    };

    struct KeyboardEvent {
        int keycode;      //code of key
        bool modAlt;      //+ alt
        bool modShift;    //+ shift
        bool modSuperKey; //fn
        bool modControl;  //+ ctrl

        enum PressType {
            PRESS_DOWN,
            PRESS_UP
        } pressType;
    };
}
}