
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CURSOR_HPP
#define WHITEGEAR_CURSOR_HPP

#include <core/typedefs.hpp>
#include <math/color.hpp>

namespace wg {
    enum cursor {
        CURSOR_DEFAULT,

        CURSOR_LAST
    };
    enum cursor_state {
        CURSOR_STATE_NORMAL,

        CURSOR_STATE_LAST
    };

    void get_cursor(color32* pixels, cursor cur, cursor_state state);
}

#endif //WHITEGEAR_CURSOR_HPP
