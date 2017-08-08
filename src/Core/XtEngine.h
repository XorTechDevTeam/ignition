/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>

#include "IXtDevice.h"

namespace xt {
    class XtEngine : public patterns::XtSingleton<XtEngine> {
    private:
        IXtDevice* _device;
    public:
        XtEngine();
        ~XtEngine() override;

        int run();

        IXtDevice* getCurrentDevice() { return _device; }
    };
}