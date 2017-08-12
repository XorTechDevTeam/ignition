//
// Created by droncode on 8/12/17.
//

#pragma once

#include <XtCommon.h>
#include <Core/IXtTime.h>

namespace xt {
namespace time {
    class XtSystemTime : public IXtTime {
    public:
        virtual double getTime() const override;
        void update() override {};
        void setMultiplier(float value) override {}
        float getMultiplier() const override { return 1.f; }
    };
}
}


