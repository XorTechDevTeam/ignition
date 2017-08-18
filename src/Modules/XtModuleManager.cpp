//
// Created by rabbitlancer on 8/15/17.
//

#include "XtModuleManager.h"
#include "XtNullModule.h"

using namespace xt;
using namespace modules;

XtModuleManager::XtModuleManager() {

}

XtModuleManager::~XtModuleManager() {
    for (auto &module : this->modules) {
        delete module;
    }
}

XtModuleManager * XtModuleManager::getInstance() {
    if (!_instance) {
        _instance = new XtModuleManager();
    }
    return _instance;
}

void XtModuleManager::release() {
    if (_instance) {
        delete _instance;
        _instance = nullptr;
    }
}

int XtModuleManager::init() {
    LOGMSG("[XtModuleManager]: initializing...");
    XtNullModule::getInstance()->init();

    LOGMSG("[XtModuleManager]: loaded %d modules.", this->modules.size());

    return 0;
}

XtModRC XtModuleManager::addModule(XtModule *module) {
    LOGMSG("[XtModuleManager]: linking module %s...", module->getName().c_str());
    this->modules.push_back(module);

    XtDependencyUnit *deps = module->getDependencies();

    auto cur = deps->nextDependency();

    int dep;
    while (cur != deps->end()) {
        dep = 0;

        for (int i = 0; i<this->modules.size(); ++i) {
            if (this->modules.at(i)->getName() == cur->first) {
                *(cur->second) = dep = i;
            }
        }

        if (dep == 0) {
            LOGMSG("[XtModuleManager]: unable to resolve dependency '%s'.", cur->first.c_str());
            return RC_UNRSLV_DEP;
        }
    }

    return RC_OK;
}

XtModuleManager *XtModuleManager::_instance = nullptr;