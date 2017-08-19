//
// Created by rabbitlancer on 8/15/17.
//

#include "XtMetadata.h"

#if defined(XT_LINUX) || defined(XT_OSX)
#include <sys/utsname.h>
#endif

using namespace xt;

XtMetadata::XtMetadata() {
    this->init();
}

void XtMetadata::init() {
#if defined(XT_LINUX) || defined(XT_OSX)
#if defined(XT_LINUX)
    this->platformName = PTLinux;
#else
    this->platformName = PTOSX;
#endif
    utsname unameData;
    uname(&unameData);
    this->subplatformName = unameData.sysname;

    String str = unameData.release;
    int dot = str.find('.');
    this->platformVerMajor = std::stoi(str.substr(0,dot));
    this->platformVerMinor = std::stoi(str.substr(dot+1, str.find('.',dot)));
#elif defined(XT_ANDROID)
    this->platformName = PTAndroid;
    //TODO: finish Android
#elif defined(XT_IOS)
    this->platformName = PTiOS;
    //TODO: finish iOS
#elif defined(XT_WINDOWS)
    this->platformName = PTWindows32;
    //TODO: finish Windows
#endif

    this->xorTechVerMajor = XT_VERSION_MAJOR;
    this->xorTechVerMinor = XT_VERSION_MINOR;
}

XtPlatformType XtMetadata::getPlatformName() const {
    return platformName;
}

const String &XtMetadata::getSubplatformName() const {
    return subplatformName;
}

int XtMetadata::getPlatformVerMajor() const {
    return platformVerMajor;
}

int XtMetadata::getPlatformVerMinor() const {
    return platformVerMinor;
}

int XtMetadata::getXorTechVerMajor() const {
    return xorTechVerMajor;
}

int XtMetadata::getXorTechVerMinor() const {
    return xorTechVerMinor;
}
