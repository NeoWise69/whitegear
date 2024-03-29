
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "logger.hpp"

#include <mutex>
#include <cstdarg>
#include <chrono>
#include <ctime>

namespace wg {

    namespace {

        inline void localtime_(struct tm* t, time_t* time) noexcept {
            if (t && time) {
#ifdef WG_WINDOWS
                localtime_s(t, time);
#elif WG_UNIX
                localtime_r(time, t);
#endif
            }
        }

#ifdef WG_WINDOWS
#   define fprintf_ fprintf_s
#elif WG_UNIX
#   define fprintf_ fprintf
#endif

        inline std::string get_date_time() noexcept {
            time_t      now = time(nullptr);
            struct tm   t = {};
            char        buf[80];
            localtime_  (&t, &now);
            strftime    (buf, sizeof(buf), "%Y-%m-%d.%X", &t);
            return      buf;
        }

        static std::mutex sMtx = {};
    }

    logger& logger::log(log_level lvl, const char *fmt, ...) noexcept {
#ifdef WG_BUILD_DEBUG
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 2048, fmt, ap);
        va_end(ap);

        std::string_view sv = {};
        FILE* stream = stdout;

        switch (lvl) {
            case LOG_LEVEL_TRACE: sv = "[trace]"; break;
            case LOG_LEVEL_INFO: sv = "[info]"; break;
            case LOG_LEVEL_WARNING: sv = "[warning]"; break;
            case LOG_LEVEL_ERROR: sv = "[error]"; stream = stderr; break;
            case LOG_LEVEL_PANIC: sv = "[panic]"; stream = stderr; break;
        }
        fprintf_(stream, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
#endif
        return *this;
    }

    logger& logger::trace(const char *fmt, ...) noexcept {
#ifdef WG_BUILD_DEBUG
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 2048, fmt, ap);
        va_end(ap);

        std::string_view sv = "[trace]";
        fprintf_(stdout, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
#endif
        return *this;
    }

    logger& logger::info(const char *fmt, ...) noexcept {
#ifdef WG_BUILD_DEBUG
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 2048, fmt, ap);
        va_end(ap);

        std::string_view sv = "[info]";
        fprintf_(stdout, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
#endif
        return *this;
    }

    logger& logger::warning(const char *fmt, ...) noexcept {
#ifdef WG_BUILD_DEBUG
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 2048, fmt, ap);
        va_end(ap);

        std::string_view sv = "[warning]";
        fprintf_(stdout, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
#endif
        return *this;
    }

    logger& logger::error(const char *fmt, ...) noexcept {
#ifdef WG_BUILD_DEBUG
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 2048, fmt, ap);
        va_end(ap);

        std::string_view sv = "[error]";
        fprintf_(stderr, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
#endif
        return *this;
    }

    logger& logger::panic(const char *fmt, ...) noexcept {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, 2048, fmt, ap);
        va_end(ap);

        std::string_view sv = "[panic]";
        fprintf_(stderr, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);

        abort();
        return *this;
    }

    logger &logger::dead_end() noexcept {
        return panic("end of program");
    }
}
