//
// Created by droncode on 8/15/17.
//

#include "XtLogManager.h"

#include <stdarg.h>

#ifdef XT_LINUX
#include <Core/Platform/Linux/XtLinuxLogService.h>
#endif

#ifdef XT_ANDROID
#include <Core/Platform/Android/XtAndroidLogService.h>
#endif

#ifdef XT_WINDOWS
#include <Core/Platform/Windows/XtWindowsLogService.h>
#endif

namespace xt {
namespace log {
    XtLogManager::XtLogManager() : _service(nullptr) {
#if defined(XT_LINUX)
        _service = static_cast<IXtLogService*>(new XtLinuxLogService());
#elif defined(XT_ANDROID)
        _service = static_cast<IXtLogService*>(new XtAndroidLogService());
#elif defined(XT_WINDOWS)
		_service = static_cast<IXtLogService*>(new XtWindowsLogService());
#endif
    }

    XtLogManager::~XtLogManager() {
        if (_service) {
            delete _service;
            _service = nullptr;
        }
    }

    XtLogManager *XtLogManager::getInstance() {
        if (!_instance) {
            _instance = new XtLogManager();
        }
        return _instance;
    }

    void XtLogManager::release() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    void XtLogManager::operator()(const char *format, ...) {
        va_list  args;
        va_start(args, format);
        char buffer[2048];
        vsprintf(buffer, format, args);

        va_end(args);

        if (_service) {
            _service->writeLog(std::string(buffer));
        }
    }
}
}

xt::log::XtLogManager* xt::log::XtLogManager::_instance = nullptr;