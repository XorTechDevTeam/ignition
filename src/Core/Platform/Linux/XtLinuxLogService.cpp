//
// Created by droncode on 8/15/17.
//

#include "XtLinuxLogService.h"

namespace xt {
namespace log {
    void XtLinuxLogService::writeLog(const std::string &message) {
        printf("INFO: %s\n", message.c_str());
    }
}
}