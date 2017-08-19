/**
 * @file XtEventQueue.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * An event queue class header.
 * Event queue stores and dispatches events to event subscribers
 * (if any) and/or event targets, if any.
 * @see XtEvent
 * @see XtModuleManager
 */

#pragma once

#include "XtEvent.h"
#include <XtCommon.h>

namespace xt {
    namespace event {
        /**
         * Defines the size of event queue.
         */
        const auto MAX_EVENTS = 1024;

        /**
         * Event queue class.
         * Utilizes a version of deque over an array. Implements a subscription map
         * for dispatching events that are meant to be broadcast.
         * Allows for event pushing, resolving and module subscription. XtEvent objects
         * are created by modules and destroyed within XtEventQueue: a module developer
         * shouldn't care about event memory management.
         */
        class XtEventQueue {
        private:
            XtEvent *queue[MAX_EVENTS];         /**< Actual event queue container.
                                                 * Holds pointers to XtEvent objects.
                                                 * Is NOT initialized, but is guaranteed to have pointers
                                                 * to real data on read.
                                                 * */
            unsigned int _head;                                     /**< Writing end of the deque. */
            unsigned int _tail;                                     /**< Reading end of the deque. */

            UnorderedMap<String, List<unsigned int> > subscribers;  /**< Map that associates event names
                                                                     * with modules that are subscribed to those
                                                                     * events.
                                                                     * */
        public:
            /**
             * Public constructor.
             * Does really nothing but initialize the deque.
             */
            XtEventQueue();

            /**
             * Pushes event to the queue.
             * As of push, the module supposedly no longer controls the event. And in no
             * circumstance it should dispose of the event object; the disposal is handled
             * by queue after resolving.
             * An overflow may lead to an unfortunate event where no events will be handled
             * during resolution, at all. This circumstance is checked but currently is not
             * dealt with in any way.
             * @param ev: pointer to an XtEvent to be queued.
             */
            void pushEvent(XtEvent *ev);

            /**
             * Resolves event in the queue.
             * Directed (with precise recipient ID) events are dispatched directly to recipient
             * module. Broadcast (with recipient = XtEvBroadcast) are dispatched consequently
             * to each module registered to an event with this name.
             * @see subscribe()
             */
            void resolveEvents();

            /**
             * Subscribes a module to an event with name evName.
             * Once subscribed, a module will handle any broadcast events with name equal to evName.
             * However, it will not intercept any directed events, so keep that in mind when designing
             * interaction between several modules of your own.
             * @param evName: the name of broadcast events that the module will handle.
             * @param subscriber: the ID of the subscriber module.
             */
            void subscribe(String evName, unsigned int subscriber);
        };
    }
}