//
// Created by droncode on 8/15/17.
//
#pragma once

#include <Core/Log/IXtLogService.h>

namespace xt {
namespace log {
    class XtAndroidLogService : public IXtLogService {
    public:
        XtAndroidLogService() {}
        ~XtAndroidLogService() {}

        void writeLog(const std::string& message) override;
    };
}
}