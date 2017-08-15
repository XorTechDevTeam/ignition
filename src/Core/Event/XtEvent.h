/**
 *	@file XtEvent.h
 *	@author Rabbitlancer
 *	@date 14 Aug 2017
 *
 *	Header file describing an event class.
 *	XtEvent is a simple block of data used to
 *	exchange event information between modules.
 */

#pragma once

#include <XtCommon.h>

namespace xt {
 	namespace event {
	 	class XtEvent {
        private:
            String sender;
            String recipient;
            String evName;
            String evContent;
        public:
            XtEvent(String recipient, String evName, String evContent, String sender);
            XtEvent(String recipient, String evName, String evContent);
            ~XtEvent();

            void setEvName(String newEvName);
            void setEvContent(String newEvContent);
            void setSender(String newSender);
            void setRecipient(String newRecipient);

            String getEvName();
            String getEvContent();
            String getSender();
            String getRecipient();
	 	};
 	}
 }