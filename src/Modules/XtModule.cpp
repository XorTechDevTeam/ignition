//
// Created by rabbitlancer on 8/15/17.
//

#include "XtModule.h"
#include <Modules/XtModuleManager.h>

using namespace xt;
using namespace modules;

mod_rc XtModule::linkModule() {
    mod_rc rc = XtModuleManager::getInstance()->addModule(this);

    switch (rc) {
        case RC_OK:
            //TODO: log about it =3
            break;
        case RC_UNRSLV_DEP:
            //TODO: log about an unresolved dependency and crash
            break;
        case RC_FAIL:
            //TODO: critically crash
            break;
    }

    return rc;
}

void XtModule::sendEvent(event::XtEvent *ev) {
    //TODO: send an event to module manager's event queue
}

XtDependencyUnit * XtModule::getDependencies() {
    return &(this->depUnit);
}

String XtModule::getName() {
    return this->moduleName;
}