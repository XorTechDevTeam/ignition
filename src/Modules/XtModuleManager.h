/**
 * @file XtModuleManager.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Header file describing XtModuleManager class.
 * @see XtModule
 */

#pragma once

#include <XtCommon.h>
#include <Modules/XtModuleCommon.h>

#include <Modules/XtModule.h>

namespace xt {
    namespace modules {
        class XtModuleManager : public patterns::XtSingleton<XtModuleManager> {
        private:
            Vector<XtModule*> modules;
        public:
            ~XtModuleManager() override;

            int init();
            mod_rc addModule(XtModule *module);
        };
    }
}