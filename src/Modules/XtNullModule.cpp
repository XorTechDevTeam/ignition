//
// Created by rabbitlancer on 8/15/17.
//

#include "XtNullModule.h"

void XTCALL whatAmIDoingHere() {
    LOGMSG("Well, you wanted me to do nothing, I'm doing nothing.");
}

using namespace xt;
using namespace modules;

XtNullModule::XtNullModule() {
    this->moduleName = "nothing";
}

XtModule * XtNullModule::getInstance() {
    return new XtNullModule();
}

int XtNullModule::init() {
    XTLOGIC->registerFunction("void whatAmIDoingHere()", asFUNCTION(whatAmIDoingHere));
    this->linkModule();
    return 0;
}

void XtNullModule::handleEvent(const event::XtEvent *ev) {
    LOGMSG("Module nothing received an event. How is that even possible?");
}
