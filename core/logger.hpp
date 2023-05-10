
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
        logger& log(log_level, const char* fmt, ...);
        logger& trace(const char* fmt, ...);
        logger& info(const char* fmt, ...);
        logger& warning(const char* fmt, ...);
        logger& error(const char* fmt, ...);
        logger& panic(const char* fmt, ...);
    };

    static logger out;
}

#endif //WHITEGEAR_LOGGER_HPP
