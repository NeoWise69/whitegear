
/*******************************************************************************
 * Copyright (c) 200023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/cursor.hpp>
#include <cstring>

#include "cursor_default_normal.hpp"

namespace wg {

    static const bounded_array<color32, 256> cursors[CURSOR_LAST][CURSOR_STATE_LAST] = {
            { // CURSOR_DEFAULT
                    { // CURSOR_STATE_NORMAL
                        cursor_default_normal,
                    }, // !CURSOR_STATE_NORMAL
                }, // !CURSOR_DEFAULT
    };

    void get_cursor(color32 pixels[256], cursor cur, cursor_state state) {
        memcpy(pixels, cursors[cur][state].data(), sizeof(color32) * 256);
    }
}
