/**
 * @file XtEventQueue.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * An event queue class header.
 * Event queue stores and dispatches events to event subscribers
 * (if any) and/or event targets, if any.
 * @see XtEvent
 */

#pragma once

#include "XtEvent.h"
#include <XtCommon.h>

namespace xt {
    namespace event {
        const auto MAX_EVENTS = 1024;

        class XtEventQueue {
        private:
            XtEvent *queue[MAX_EVENTS];

        public:

        };
    }
}