/**
 * XorTech Source Code
 */
#include <XtCommon.h>
#include "XtEngine.h"

XT_ENTRY
{
#if defined(XT_WINDOWS) && XT_WINDOWS == WIN32
	xt::win32::g_win32AppInstance = hInstance;
#endif

    LOGMSG("*** XT ENTRY ***");

    xt::XtDeviceParams deviceParams = xt::platform::g_xtDebugDevice;

    if (!xt::XtEngine::getInstance()->init(deviceParams)) {
        LOGMSG("Unable to init XtEngine");
        return -1;
    }

#if !defined(XT_ANDROID) && !defined(XT_IOS)    //У Android & IOS свои циклы
    while (xt::XtEngine::getInstance()->isOnline()) {
        xt::XtEngine::getInstance()->update();
    }

    xt::XtEngine::release();
#endif
    return 0;
}