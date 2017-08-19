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
    //TODO: Iterate engine
    xt::XtEngine::getInstance()->update();
}

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnPause(JNIEnv * env, jobject obj) {
    LOGMSG("*** Android::onPause called ***");
    xt::XtEngine::getInstance()->pause();
}

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnResume(JNIEnv * env, jobject obj) {
    LOGMSG("*** Android::onResume called ***");
    xt::XtEngine::getInstance()->resume();
}

JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnDestroy(JNIEnv * env, jobject obj) {
    LOGMSG("*** Android::onDestroy called ***");
    xt::XtEngine::getInstance()->offline(); //close loop
    xt::XtEngine::release();
}
#endif