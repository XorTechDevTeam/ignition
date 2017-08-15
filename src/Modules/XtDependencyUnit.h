/**
 * @file DependencyUnit.h
 * @author Rabbitlancer
 * @date 15 Aug 2017
 *
 * Header for DependencyUnit class.
 * DependencyUnit handles data about the module's
 * dependent modules (the ones that module will
 * send events to).
 * @see XtModule
 */

#pragma once

namespace xt {
    namespace modules {
        class XtDependencyUnit {
        private:
            UnorderedMap<String, int*> deps;
            UnorderedMap<String, int*>::const_iterator cur;
        public:
            XtDependencyUnit();
            ~XtDependencyUnit();
            void addDependency(String depName, int *index);
            UnorderedMap<String, int*>::const_iterator nextDependency();
            UnorderedMap<String, int*>::const_iterator end();
        };
    }
}