//
// Created by droncode on 8/12/17.
//
#pragma once

#ifdef XT_ANDROID
#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <XtCommon.h>

extern "C" {
    JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtInit(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtUpdate(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnPause(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnResume(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_xtengine_XtAndroid_XtEngine_xtOnDestroy(JNIEnv * env, jobject obj);
};

#else
#error Invalid platform
#endif