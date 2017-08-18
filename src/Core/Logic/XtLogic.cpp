//
// Created by rabbitlancer on 8/17/17.
//

#include "XtLogic.h"
#include "XtCall.h"
//TODO: stdstring addon

using namespace xt;
using namespace logic;

void XtLogic::messageCallback(const asSMessageInfo *msg, void *param) {
    //TODO: well you know what to do about it
}

XtLogic::XtLogic() {
    this->asEngine = asCreateScriptEngine();
    this->asEngine->SetMessageCallback(asFUNCTION(XtLogic::messageCallback),nullptr, asXTCALL);
}

XtLogic::~XtLogic() {
    this->asEngine->ShutDownAndRelease();
}

int XtLogic::registerFunction(String &name, asSFuncPtr &m) {
    //TODO: checks and whistles

    this->asEngine->RegisterGlobalFunction(name.c_str(), m, asXTCALL);

    return 0;
}

int XtLogic::registerMethod(String &name, String &object, asSFuncPtr &m) {
    //TODO: ...well, y'know

    this->asEngine->RegisterObjectMethod(object.c_str(), name.c_str(), m, asCALL_THISCALL);

    return 0;
}