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

using namespace xt;
using namespace xt::platform;

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtInit(JNIEnv * env, jobject obj,  jint width, jint height) {
    xt::platform::g_xtDebugDevice = xt::XtDeviceParams(width, height, true);    //android always fullscreen, exclude Samsung tablets
    XT_main();
}

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtUpdate(JNIEnv * env, jobject obj) {
    IXtPlatform* platform = XtEngine::getInstance()->getCurrentPlatform();
    IXtRenderDevice* render = nullptr;
    if (platform && (render = platform->getRenderDevice())) {
        XtEngine::getInstance()->update();
        platform->onDeviceUpdate();
        render->drawFrame(0.f);
    }
}

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnPause(JNIEnv * env, jobject obj) {
    //TODO: Call engine here
}

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnResume(JNIEnv * env, jobject obj) {
    //TODO: Call engine here
}
#endif