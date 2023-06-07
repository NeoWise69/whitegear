
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "time.hpp"

#include <chrono>

namespace wg {
    double time_point::get(time_point::e_resolution resolution) const noexcept {
        switch (resolution) {
            case e_resolution::nanoseconds:     return (mTimeInNanoseconds);
            case e_resolution::milliseconds:    return mTimeInNanoseconds * (0.000001);
            case e_resolution::seconds:         return mTimeInNanoseconds * (1e-9);
            case e_resolution::minutes:         return mTimeInNanoseconds * (1.66667e-11);
            case e_resolution::hours:           return mTimeInNanoseconds * (2.778e-13);
        }
        return mTimeInNanoseconds;
    }

    time_point time_point::now() noexcept {
        // should return if nanoseconds, since std::chrono::steady_clock works with ns.
        return double(std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(std::chrono::system_clock::now().time_since_epoch()).count());
    }

    time_point operator+(const time_point& a, const time_point& b) noexcept {
        return a.get(time_point::nanoseconds) + b.get(time_point::nanoseconds);
    }
    time_point operator-(const time_point& a, const time_point& b) noexcept {
        return a.get(time_point::nanoseconds) - b.get(time_point::nanoseconds);
    }

    time_point operator""_h(const long double t) noexcept {
        return (double)(t * 3600000000000);
    }

    time_point operator""_m(const long double t) noexcept {
        return (double)(t * 60000000000);
    }

    time_point operator""_s(const long double t) noexcept {
        return (double)(t * 1000000000);
    }

    time_point operator""_ms(const long double t) noexcept {
        return (double)(t * 1000000);
    }

    time_point operator""_ns(const long double t) noexcept {
        return double(t);
    }

}
