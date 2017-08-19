/**
 * @file XtLogic.h
 * @author Rabbitlancer
 * @date 17 Aug 2017
 *
 * Заголовочный файл для окружения AngelScript.
 */

#pragma once

#include <XtCommon.h>
#include <angelscript.h>

namespace xt {
    namespace logic {
        class XtLogic {
        private:
            static XtLogic *_instance;

            asIScriptEngine *asEngine;

            XtLogic();
            ~XtLogic();

            void messageCallback(const asSMessageInfo *msg, void *param);
        public:
            static XtLogic *getInstance();
            static void release();

            int registerFunction(String name, asSFuncPtr m);
            int registerMethod(String name, String object, asSFuncPtr m);
        };
    }
}