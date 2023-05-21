
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <runtime/user_input.hpp>

namespace wg {
    input &input::get() {
        static input instance = {};
        std::lock_guard lk(instance.mMtx);
        return instance;
    }

    void input_device::process_release_keys() {
        auto& rc = mState.release_keys;
        for (u8 i = 0; i < rc.size(); ++i) {
            key k = rc[i];
            mState.keys[k] = KEY_STATE_IDLE;
        }
        rc.clear();
    }
}
