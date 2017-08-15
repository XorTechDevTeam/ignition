//
// Created by rabbitlancer on 8/15/17.
//

#include "XtEvent.h"

using namespace xt;
using namespace event;

XtEvent::XtEvent(String recipient, String evName, String evContent, String sender) {
    this->recipient = recipient;
    this->evName = evName;
    this->evContent = evContent;
    this->sender = sender;
}
