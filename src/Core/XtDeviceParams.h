//
// Created by droncode on 8/12/17.
//
#pragma once

#include <XtCommon.h>

namespace xt {
    /**
     * @brief Базовые параметры рендера
     */
    struct XtDeviceParams {
        int width;
        int height;
        bool fullscreen;

        XtDeviceParams(): width(XT_SCREEN_MIN_WIDTH),
                          height(XT_SCREEN_MIN_HEIGHT),
                          fullscreen(false) {}

        XtDeviceParams(int w, int h, bool fs) : width(w),
                                                height(h),
                                                fullscreen(fs) {}
    };
}
