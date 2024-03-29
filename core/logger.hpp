
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_LOGGER_HPP
#define WHITEGEAR_LOGGER_HPP

#include "typedefs.hpp"

namespace wg {
    enum log_level {
        LOG_LEVEL_TRACE,
        LOG_LEVEL_INFO,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_PANIC,
    };

    class logger {
    public:
        logger& log(log_level, const char* fmt, ...) noexcept;
        logger& trace(const char* fmt, ...) noexcept;
        logger& info(const char* fmt, ...) noexcept;
        logger& warning(const char* fmt, ...) noexcept;
        logger& error(const char* fmt, ...) noexcept;
        logger& panic(const char* fmt, ...) noexcept;
        logger& dead_end() noexcept;
    };

    static logger out;

#define WG_NOT_IMPLEMENTED   \
    {                        \
        out.warning("Called \'%s()\', but was not implemented yet! (%s:%d)", __func__, __FILE__, __LINE__); \
    }
}

#endif //WHITEGEAR_LOGGER_HPP
