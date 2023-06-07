
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <cassert>
#include "ref_counted.hpp"

namespace wg {
    ref_counted::ref_counted() noexcept : rc(new ref_count()) {
        ++(rc->weak_refs);
    }
    ref_counted::~ref_counted() noexcept {
        assert(rc);
        assert(rc->refs == 0);
        assert(rc->weak_refs > 0);
        rc->refs = -1;
        --(rc->weak_refs);
        if (!(rc->weak_refs)) {
            delete rc;
        }
        rc = nullptr;
    }

    void ref_counted::inc_ref() noexcept {
        assert(rc->refs >= 0);
        ++(rc->refs);
    }

    void ref_counted::dec_ref() noexcept {
        assert(rc->refs > 0);
        --(rc->refs);
    }
}
