/**
 * @file XtLogic.h
 * @author Rabbitlancer
 * @date 17 Aug 2017
 *
 * Заголовочный файл для окружения AngelScript.
 */

#include <XtCommon.h>
#include <angelscript.h>

namespace xt {
    namespace logic {
        class XtLogic {
        private:
            asIScriptEngine *asEngine;

            void messageCallback(const asSMessageInfo *msg, void *param);
        public:
            XtLogic();
            ~XtLogic();
            int registerFunction(String &name, asSFuncPtr &m);
            int registerMethod(String &name, String &object, asSFuncPtr &m);
        };
    }
}