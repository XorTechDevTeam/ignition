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
        /**
         * Return code for module linking.
         * Has three values of different fail severity.
         */
        enum XtModRC {
            RC_OK, /**< Module successfully linked into manager. */
            RC_UNRSLV_DEP, /**< Module has an unresolved dependency. */
            RC_FAIL /**< Any other error. */
        };
    }
}
