//
// Created by droncode on 8/15/17.
//

#pragma once

#include <XtCommon.h>
#include <Core/Log/IXtLogService.h>

namespace xt {
namespace log {
    class XtLinuxLogService : public IXtLogService {
    public:
        void writeLog(const std::string& message) override;
    };
}
}


