//
// Created by droncode on 8/12/17.
//
#if defined(XT_ANDROID)
#include <XtCommon.h>
#include <Core/XtEngine.h>
#include <Core/PlatformEntry.h>
#include <Core/Platform/Android/XtDefaultDevice.h>
#include <Core/Render/IXtRenderDevice.h>

#include "XtAndroidNative.h"
#include <Core/Platform/Android/XtAndroidProject.h>

using namespace xt;
using namespace xt::platform;

XT_INIT_FUNC {
    xt::platform::g_xtDebugDevice = xt::XtDeviceParams(width, height, true);    //android always fullscreen, exclude Samsung tablets
    #if defined(XT_BUILD_DATE)
        LOGMSG("> %s", XT_BUILD_DATE);
    #else
        LOGMSG("> Notice: unknown build tags");
    #endif
    XT_main();
}

XT_UPDATE_FUNC {
    //TODO: Iterate engine
    xt::XtEngine::getInstance()->update();
}

XT_PAUSE_FUNC {
    LOGMSG("*** Android::onPause called ***");
    xt::XtEngine::getInstance()->pause();
}

XT_RESUME_FUNC {
    LOGMSG("*** Android::onResume called ***");
    xt::XtEngine::getInstance()->resume();
}

XT_DESTROY_FUNC {
    LOGMSG("*** Android::onDestroy called ***");
    xt::XtEngine::getInstance()->offline(); //close loop
    xt::XtEngine::release();
}
#endif