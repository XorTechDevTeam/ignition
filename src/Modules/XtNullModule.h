/**
 * @file XtNullModule.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Behold the null module.
 * A null module is the module that occupies
 * the "broadcast" index 0. Null module is
 * nothing and does nothing. Just a waste of
 * space in general.
 * @see XtModuleManager
 */

#pragma once

#include <Modules/XtModule.h>

namespace xt {
    namespace modules {
        class XtNullModule : public XtModule {
        private:
            XtNullModule();
        public:
            static XtModule *getInstance();
            int init() final;
            void handleEvent(event::XtEvent *ev) final;
        };
    }
}