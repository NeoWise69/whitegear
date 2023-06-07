
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_TIME_HPP
#define WHITEGEAR_TIME_HPP

#include <core/typedefs.hpp>

namespace wg {
    class time_point {
    public:
        inline time_point() noexcept = default;
        inline ~time_point() noexcept = default;
        inline time_point(double ns) noexcept : mTimeInNanoseconds(ns) {}

        enum e_resolution : uint {
            nanoseconds,
            milliseconds,
            seconds,
            minutes,
            hours
        };
        double get(e_resolution resolution) const noexcept;

        static time_point now() noexcept;
    private:
        double mTimeInNanoseconds = {};
    };
    time_point operator+(const time_point& a, const time_point& b) noexcept;
    time_point operator-(const time_point& a, const time_point& b) noexcept;

    time_point operator""_h(const long double t) noexcept;
    time_point operator""_m(const long double t) noexcept;
    time_point operator""_s(const long double t) noexcept;
    time_point operator""_ms(const long double t) noexcept;
    time_point operator""_ns(const long double t) noexcept;

    struct frame_time_stats {
        // general
        time_point frame_time;
        time_point tick_time;
        // frame related
        time_point frame_begin_time;
        time_point frame_end_time;

        time_point world_tick_time;
        time_point delta_time;
    };
    inline frame_time_stats GTimeStats;
}

#endif //WHITEGEAR_TIME_HPP
