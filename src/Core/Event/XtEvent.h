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
		const auto XtEvBroadcast = 0;

	 	class XtEvent {
        private:
            unsigned int sender;
            unsigned int recipient;
            String evName;
            String evContent;
        public:
            XtEvent(unsigned int sender, unsigned int recipient, String evName, String evContent);
            ~XtEvent();

            void setEvName(String newEvName);
            void setEvContent(String newEvContent);
			void setRecipient(unsigned int newRecp);

            String &getEvName();
            String &getEvContent();
            unsigned int getSender();
            unsigned int getRecipient();
	 	};
 	}
 }