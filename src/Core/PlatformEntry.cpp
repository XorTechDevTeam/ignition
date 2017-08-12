/**
 * XorTech Source Code
 */
#include <XtCommon.h>
#include "XtEngine.h"

XT_ENTRY
{
    xt::XtDeviceParams deviceParams = xt::platform::g_xtDebugDevice;

    if (!xt::XtEngine::getInstance()->init(deviceParams)) {
        //TODO: log it
        return -1;
    }
    int exitCode = xt::XtEngine::getInstance()->run();
#if !defined(XT_ANDROID) && !defined(XT_IOS)
    xt::XtEngine::release();
#endif
    return exitCode;
}