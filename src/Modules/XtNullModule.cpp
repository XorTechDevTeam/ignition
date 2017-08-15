//
// Created by rabbitlancer on 8/15/17.
//

#include "XtNullModule.h"

using namespace xt;
using namespace modules;

XtNullModule::XtNullModule() {
    this->moduleName = "nothing";
}

XtModule * XtNullModule::getInstance() {
    return new XtNullModule();
}

int XtNullModule::init() {
    return 0;
}

void XtNullModule::handleEvent(event::XtEvent *ev) {
    //TODO: well, why not log about it?
}
