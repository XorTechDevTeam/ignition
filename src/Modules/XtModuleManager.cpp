//
// Created by rabbitlancer on 8/15/17.
//

#include "XtModuleManager.h"
#include "XtNullModule.h"

using namespace xt;
using namespace modules;

XtModuleManager::~XtModuleManager() {
    for (auto &module : this->modules) {
        delete module;
    }
}

int XtModuleManager::init() {
    this->addModule(XtNullModule::getInstance());

    return 0;
}

mod_rc XtModuleManager::addModule(XtModule *module) {
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

        if (dep == 0) return RC_UNRSLV_DEP;
    }

    return RC_OK;
}