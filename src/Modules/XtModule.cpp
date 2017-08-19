//
// Created by rabbitlancer on 8/15/17.
//

#include "XtModule.h"
#include <Modules/XtModuleManager.h>

using namespace xt;
using namespace modules;

void XtModule::setId(unsigned int id) {
    this->_id = id;
}

XtModRC XtModule::linkModule() {
    XtModRC rc = XtModuleManager::getInstance()->addModule(this);

    switch (rc) {
        case RC_OK:
            LOGMSG("[%s]: linked successfully, id: %d", this->moduleName.c_str(), this->_id);
            break;
        case RC_UNRSLV_DEP:
            LOGMSG("[%s]: this module has an unresolved dependency!", this->moduleName.c_str());
            break;
        case RC_FAIL:
            LOGMSG("[%s]: ERROR INITIALIZING MODULE", this->moduleName.c_str());
            break;
    }

    return rc;
}

void XtModule::sendEvent(event::XtEvent *ev) {
    XtModuleManager::getInstance()->sendEvent(ev);
}

XtDependencyUnit * XtModule::getDependencies() {
    return &(this->depUnit);
}

String XtModule::getName() {
    return this->moduleName;
}