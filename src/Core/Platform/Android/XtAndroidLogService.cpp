//
// Created by droncode on 8/15/17.
//
#include "XtAndroidLogService.h"
#include <XtCommon.h>

namespace xt {
namespace log {
    void XtAndroidLogService::writeLog(const std::string& message) {
        __android_log_print(ANDROID_LOG_INFO, "XTE", "%s", message.c_str());
    }
}
}