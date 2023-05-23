
/*******************************************************************************
 * Copyright (c) 200023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/cursor.hpp>

#include "cursor_default.hpp"

namespace wg {
    /**
     * Reserved (hardcoded) array of cursors, where every cursor should match
     * size to (32x32x4).
     */
    static const bounded_array<color32, 1024> cursors[CURSOR_LAST][CURSOR_STATE_LAST] = {
            { // CURSOR_SYSTEM
                    {}, // CURSOR_STATE_NORMAL
                }, // !CURSOR_SYSTEM
            { // CURSOR_DEFAULT
                    { // CURSOR_STATE_NORMAL
                        cursor_default,
                    }, // !CURSOR_STATE_NORMAL
                }, // !CURSOR_DEFAULT
    };

    void get_cursor(color32* pixels, cursor cur, cursor_state state) {
        const auto& selected_cursor = cursors[cur][state];
        memcpy(pixels, selected_cursor.data(), sizeof(color32) * selected_cursor.size());
    }
}
