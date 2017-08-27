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
#include <Core/Platform/Android/XtAndroidProject.h>

extern "C" {
	XT_INIT_FUNC;
	XT_UPDATE_FUNC;
	XT_PAUSE_FUNC;
	XT_RESUME_FUNC;
	XT_DESTROY_FUNC;
};

#else
#error Invalid platform
#endif