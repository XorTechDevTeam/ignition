//
// Created by droncode on 8/12/17.
//

#include "XtSystemTime.h"

namespace xt {
namespace time {
    double XtSystemTime::getTime() const {
        using namespace std::chrono;

        auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
        double secsInNanosec = 0.000000001;
        return secsInNanosec * std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }
}
}