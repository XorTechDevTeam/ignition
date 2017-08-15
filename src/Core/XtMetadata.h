/**
 * @file XtMetadata.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Заголовок класса метаданных сборки.
 * Метаданные включают в себя сведения о платформе,
 * версию движка и доступные модули.
 */

#pragma once

#include <XtCommon.h>

namespace xt {
    enum PlatformType {
        PTLinux,
        PTOSX,
        PTWindows32,
        PTWindowsUWP,
        PTAndroid,
        PTiOS,
        PTEmscripten
    };

    class XtMetadata {
    private:
        PlatformType platformName;
        String subplatformName;
        int platformVerMajor;
        int platformVerMinor;
        int xorTechVerMajor;
        int xorTechVerMinor;
        //TODO: modules

        void init();
    public:
        XtMetadata();

        PlatformType getPlatformName() const;
        const String &getSubplatformName() const;
        int getPlatformVerMajor() const;
        int getPlatformVerMinor() const;
        int getXorTechVerMajor() const;
        int getXorTechVerMinor() const;
    };
}