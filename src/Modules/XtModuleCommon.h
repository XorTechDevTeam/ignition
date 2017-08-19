/**
 * @file XtModuleCommon.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Common types and whistles for module system.
 */

#pragma once

#include <Core/Logic/XtCall.h>
#include <Core/Logic/XtLogic.h>

#define XTLOGIC xt::logic::XtLogic::getInstance()

namespace xt {
    namespace modules {
        enum XtModRC {
            RC_OK, //module successfully linked into manager
            RC_UNRSLV_DEP, //module has an unresolved dependency
            RC_FAIL //any other error
        };
    }
}
