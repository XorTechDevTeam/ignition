/**
 *	@file XtModule.h
 *	@author Rabbitlancer
 *	@date 14 Aug 2017
 *
 *	Header file describing a module interface.
 *	A module is a (sometimes optional) part of
 *	XorTech engine, providing shared communication
 *	capabilities using event queue.
 *
 *	@see XtEvent
 */

#pragma once

#include <Modules/XtModuleCommon.h>

#include <Core/Event/XtEvent.h>
#include <Modules/XtDependencyUnit.h>

namespace xt {
	namespace modules {
		class XtModule {
		protected:
			unsigned int _id;
			String moduleName;
            XtDependencyUnit depUnit;
		public:
            virtual int init() = 0;
            virtual ~XtModule() = default;

			void setId(unsigned int id);
			XtModRC linkModule();

			void sendEvent(event::XtEvent *ev);
			virtual void handleEvent(event::XtEvent *ev) = 0;

			String getName();
			XtDependencyUnit *getDependencies();
		};
	}
}