//
// Created by rabbitlancer on 8/15/17.
//

#include "XtEvent.h"

using namespace xt;
using namespace event;

XtEvent::XtEvent(unsigned int sender, unsigned int recipient, String evName, String evContent) {
    this->sender = sender;
    this->recipient = recipient;
    this->evName = evName;
    this->evContent = evContent;
}

XtEvent::~XtEvent() {

}

void XtEvent::setEvName(String newEvName) {
    this->evName = newEvName;
}

void XtEvent::setEvContent(String newEvContent) {
    this->evContent = newEvContent;
}

void XtEvent::setRecipient(unsigned int newRecp) {
    this->recipient = newRecp;
}

String &XtEvent::getEvName() {
    return this->evName;
}

String &XtEvent::getEvContent() {
    return this->evContent;
}

unsigned int XtEvent::getSender() {
    return this->sender;
}

unsigned int XtEvent::getRecipient() {
    return this->recipient;
}