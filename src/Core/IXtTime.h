//
// Created by droncode on 8/12/17.
//
#pragma once

namespace xt {
    class IXtTime {
    protected:
        float _timeMultiplier = 1.0f;
    public:
        virtual ~IXtTime() {}

        virtual double getTime() const = 0;
        virtual void update() = 0;
        virtual void setMultiplier(float value) { _timeMultiplier = value; }
        virtual float getMultiplier() const { return _timeMultiplier; }
    };
}