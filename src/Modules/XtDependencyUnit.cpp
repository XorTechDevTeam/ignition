//
// Created by rabbitlancer on 8/15/17.
//

#include <XtCommon.h>
#include "XtDependencyUnit.h"

using namespace xt;
using namespace modules;

XtDependencyUnit::XtDependencyUnit() {
    this->cur = this->deps.begin();
}

XtDependencyUnit::~XtDependencyUnit() {
    this->deps.clear();
}

void XtDependencyUnit::addDependency(String depName, int *index) {
    this->deps[depName] = index;
}

UnorderedMap<String, int*>::const_iterator XtDependencyUnit::nextDependency() {
    auto retval = this->cur;
    if (this->cur != this->deps.end()) this->cur++;
    return retval;
}

UnorderedMap<String, int*>::const_iterator XtDependencyUnit::end() {
    return this->deps.end();
};