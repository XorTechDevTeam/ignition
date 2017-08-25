//
// Created by droncode on 8/25/17.
//
#pragma once

#include <XtCommon.h>

namespace xt {
namespace filesystem {
    enum XtWriteMode : uint8_t {
        XT_APPEND_FRONT,
        XT_APPEND_BACK,
        XT_OFFSET
    };
}
}