/**
 * XorTech Source Code
 */
#pragma once

#include <XtCommon.h>
#include <Core/Input/XtInputManager.h>
#include "IXtDevice.h"

namespace xt {
    using namespace input;

    class XtEngine : public patterns::XtSingleton<XtEngine> {
    private:
        IXtDevice*      _device;
        XtInputManager* _inputManager;
    public:
        XtEngine();
        ~XtEngine() override;

        int run();

        IXtDevice* getCurrentDevice() { return _device; }
        XtInputManager* getInputManager() { return _inputManager; }
    };
}