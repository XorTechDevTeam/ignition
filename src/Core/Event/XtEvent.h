/**
 *	@file XtEvent.h
 *	@author Rabbitlancer
 *	@date 14 Aug 2017
 *
 *	Header file describing an event class.
 *	XtEvent is a simple block of data used to
 *	exchange event information between modules.
 *	@see XtEventQueue
 */

#pragma once

#include <XtCommon.h>

namespace xt {
 	namespace event {
		const auto XtEvBroadcast = 0;

	 	class XtEvent {
        private:
            unsigned int sender;        /**< Sender ID. Normally the ID of the module sending the event. */
            unsigned int recipient;     /**< Recipient ID.
                                         * This is an ID of the module that will receive the actual event.
                                         * It can be XtEvBroadcast constant (for broadcasting to subscribed
                                         * modules) or an ID determined after linking by it's symbolic name.
                                         * @see XtDependencyUnit
                                         * @see XtModuleManager
                                         * */
            String evName;              /**< Event name string. */
            String evContent;           /**< Event contents. */
        public:
            /**
             * XtEvent public constructor.
             * Initializes event fields.
             * @param sender: sender field
             * @param recipient: recipient field
             * @param evName: evName field
             * @param evContent: evContent field
             * @see XtEvent
             */
            XtEvent(unsigned int sender, unsigned int recipient, String evName, String evContent);

            /**
             * XtEvent public destructor.
             * Does nothing.
             */
            ~XtEvent();

            /**
             * Setter method for evName.
             * @param newEvName
             */
            void setEvName(String newEvName);

            /**
             * Setter method for evContent.
             * @param newEvContent
             */
            void setEvContent(String newEvContent);

            /**
             * Setter method for recipient.
             * Not recommended for use unless you know what you are doing.
             * Usually, the recipient gets changed when an event is passing through subscription checks.
             * @param newRecp
             */
			void setRecipient(unsigned int newRecp);

            /**
             * Getter method for evName.
             * @return evName value.
             */
            String &getEvName();

            /**
             * Getter method for evContent.
             * @return evContent value.
             */
            String &getEvContent();

            /**
             * Getter method for sender.
             * @return sender ID.
             */
            unsigned int getSender();

            /**
             * Getter method for recipient.
             * @return recipient ID. Returns 0 if meant to broadcast, but not while dispatching.
             */
            unsigned int getRecipient();
	 	};
 	}
 }