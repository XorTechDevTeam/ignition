//
// Created by droncode on 8/25/17.
//
#pragma once

#include <XtCommon.h>

namespace xt {
namespace filesystem {
    enum XtFileOperationError : uint8_t {
        XT_NO_ERROR = 0,
        XT_FILE_NOT_EXISTS,
        XT_LARGE_FILE
    };
}
}