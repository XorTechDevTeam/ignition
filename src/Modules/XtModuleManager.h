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
#include <Core/Event/XtEventQueue.h>
#include <Modules/XtModuleCommon.h>
#include <Modules/XtModule.h>

namespace xt {
    namespace modules {
        class XtModuleManager  {
        private:
            static XtModuleManager *_instance;
            Vector<XtModule*> modules;

            event::XtEventQueue *_evQueue;

            XtModuleManager();
            ~XtModuleManager();
        public:

            static XtModuleManager *getInstance();
            static void release();

            XtModuleManager(const XtModuleManager& copy)            = delete;
            XtModuleManager(const XtModuleManager&& move)           = delete;
            XtModuleManager& operator=(const XtModuleManager& copy) = delete;
            XtModuleManager& operator=(XtModuleManager&& move)      = delete;

            int init();
            XtModRC addModule(XtModule *module);

            void sendEvent(event::XtEvent *ev);
            void dispatchEvent(event::XtEvent *ev);
            void resolveEvents();
        };
    }
}