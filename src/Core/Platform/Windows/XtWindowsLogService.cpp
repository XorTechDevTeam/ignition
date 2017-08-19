//
// Created by droncode on 8/15/17.
//

#include "XtWindowsLogService.h"

namespace xt {
namespace log {
    void XtWindowsLogService::writeLog(const std::string &message) {
		OutputDebugString("INFO: ");
		OutputDebugString(message.c_str());
		OutputDebugString("\n");
	}
}
}