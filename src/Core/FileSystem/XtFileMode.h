//
// Created by droncode on 8/25/17.
//
#pragma once

#include <XtCommon.h>

namespace xt {
namespace filesystem {
    enum XtFileMode : int {
        XT_WRITE = 0x1,
        XT_READ = 0x2,
        XT_BINARY = 0x4,
        XT_APPEND = 0x8
    };
}
}