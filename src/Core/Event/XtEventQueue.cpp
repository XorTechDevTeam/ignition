//
// Created by rabbitlancer on 8/15/17.
//

#include <Modules/XtModuleManager.h>
#include "XtEventQueue.h"

using namespace xt;
using namespace event;

XtEventQueue::XtEventQueue() {
    this->_head = 0;
    this->_tail = 0;
}

void XtEventQueue::pushEvent(XtEvent *ev) {
    if (_head == _tail - 1 || (_head == MAX_EVENTS - 1 && _tail == 0)) {
        //TODO: that's very very bad
    }

    this->queue[_head] = ev;

    ++_head;
    if (_head == MAX_EVENTS) {
        _head = 0;
    }
}

void XtEventQueue::resolveEvents() {
    XtEvent *cur;

    while (_tail != _head) {
        cur = this->queue[_tail];
        if (cur->getRecipient()) {
            modules::XtModuleManager::getInstance()->dispatchEvent(cur);
        } else {
            auto subs = this->subscribers.find(cur->getEvName());

            if (subs != this->subscribers.end()) {
                for (auto &sub : this->subscribers[cur->getEvName()]) {
                    cur->setRecipient(sub);
                    modules::XtModuleManager::getInstance()->dispatchEvent(cur);
                }
            }
        }

        delete cur;

        ++_tail;
        if (_tail == MAX_EVENTS) {
            _tail = 0;
        }
    }
}

void XtEventQueue::subscribe(String evName, unsigned int subscriber) {
    this->subscribers[evName].push_front(subscriber);
}