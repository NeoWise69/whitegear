
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "core.hpp"

#include <mutex>
#include <cstdarg>
#include <chrono>

namespace wg {

    namespace {
        inline std::string get_date_time() {
            time_t     now = time(nullptr);
            struct tm  t = {};
            char       buf[80];
            localtime_s(&t, &now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &t);
            return buf;
        }

        static std::mutex sMtx = {};
    }

    logger& logger::log(log_level lvl, const char *fmt, ...) {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsprintf_s(buf, fmt, ap);
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
        fprintf_s(stream, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
        return *this;
    }

    logger& logger::trace(const char *fmt, ...) {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
        va_start(ap, fmt);
        vsprintf_s(buf, fmt, ap);
        va_end(ap);

        std::string_view sv = "[trace]";
        fprintf_s(stdout, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
        return *this;
    }

    logger& logger::info(const char *fmt, ...) {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
                va_start(ap, fmt);
        vsprintf_s(buf, fmt, ap);
                va_end(ap);

        std::string_view sv = "[info]";
        fprintf_s(stdout, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
        return *this;
    }

    logger& logger::warning(const char *fmt, ...) {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
                va_start(ap, fmt);
        vsprintf_s(buf, fmt, ap);
                va_end(ap);

        std::string_view sv = "[warning]";
        fprintf_s(stdout, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
        return *this;
    }

    logger& logger::error(const char *fmt, ...) {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
                va_start(ap, fmt);
        vsprintf_s(buf, fmt, ap);
                va_end(ap);

        std::string_view sv = "[error]";
        fprintf_s(stderr, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
        return *this;
    }

    logger& logger::panic(const char *fmt, ...) {
        std::scoped_lock lock(sMtx);

        char buf[2048] = {};
        va_list ap;
                va_start(ap, fmt);
        vsprintf_s(buf, fmt, ap);
                va_end(ap);

        std::string_view sv = "[panic]";
        fprintf_s(stderr, "%s.%s: %s\n", get_date_time().c_str(), sv.data(), buf);
        return *this;
    }
}
