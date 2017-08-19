/**
 * @file XtNullModule.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Behold the null module.
 * A null module is the module that occupies
 * the "broadcast" index 0. Null module is
 * nothing and does nothing. Just a waste of
 * space in general.
 * @see XtModuleManager
 */

#pragma once

#include <Modules/XtModule.h>

void XTCALL whatAmIDoingHere();

class XtNullModule : public xt::modules::XtModule {
private:
    XtNullModule();
public:
    static xt::modules::XtModule *getInstance();
    int init() final;
    void handleEvent(xt::event::XtEvent *ev) final;
};