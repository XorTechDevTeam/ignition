//
// Created by rabbitlancer on 8/17/17.
//

#include "XtLogic.h"
#include "XtCall.h"
//TODO: stdstring addon

using namespace xt;
using namespace logic;

XtLogic::XtLogic() {
    LOGMSG("*** Init XtLogic ***");
    this->asEngine = asCreateScriptEngine();
    this->asEngine->SetMessageCallback(asMETHOD(XtLogic,messageCallback), nullptr, asCALL_THISCALL);
    LOGMSG("[XtLogic]: AngelScript environment set up.");
}

XtLogic::~XtLogic() {
    this->asEngine->ShutDownAndRelease();
}

void XtLogic::messageCallback(const asSMessageInfo *msg, void *param) {
    LOGMSG("[XtLogic]: received AngelScript callback");
}

XtLogic *XtLogic::getInstance() {
    if (!_instance) {
        _instance = new XtLogic();
    }
    return _instance;
}

void XtLogic::release() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

int XtLogic::registerFunction(String name, asSFuncPtr m) {
    LOGMSG("[XtLogic]: registering function %s...", name.c_str());
    //TODO: checks and whistles

    this->asEngine->RegisterGlobalFunction(name.c_str(), m, asXTCALL);

    LOGMSG("[XtLogic]: registered successfully.");
    return 0;
}

int XtLogic::registerMethod(String name, String object, asSFuncPtr m) {
    LOGMSG("[XtLogic]: registering method %s in class %s...", name.c_str(), object.c_str());
    //TODO: ...well, y'know

    this->asEngine->RegisterObjectMethod(object.c_str(), name.c_str(), m, asCALL_THISCALL);

    return 0;
}

XtLogic *XtLogic::_instance = nullptr;