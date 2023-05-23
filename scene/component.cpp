
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <scene/component.hpp>
#include <algorithm>

namespace wg {
    component_id get_available_id() {
        static u64 counter = 0;
        return counter++;
    }

    void footprint::set(i32 k) {
        mFp[k / INT_BITS] |= (1U << (k % INT_BITS));
    }

    void footprint::set(i32 k, bool val) {
        if (val) {
            set(k);
        }
        else {
            reset(k);
        }
    }

    void footprint::reset(i32 k) {
        mFp[k / INT_BITS] &= ~(1U << (k % INT_BITS));
    }

    void footprint::reset() {
        std::fill_n(mFp, MAX_COMPONENTS, 0);
    }

    i32 footprint::test(i32 k) const {
        return ( (mFp[k / INT_BITS] & (1U<<(k % INT_BITS))) != 0 );
    }

    void footprint::flip(i32 k) {
        mFp[k / INT_BITS] ^= (1U << (k % INT_BITS));
    }

    i32 footprint::operator[](i32 i) const {
        return mFp[i];
    }

    footprint &footprint::operator&=(const footprint &o) {
        for (uint i = 0; i < MAX_COMPONENTS; ++i)
            mFp[i] &= o.mFp[i];
        return *this;
    }

    footprint operator&(const footprint& a, const footprint& b) {
        return footprint(a) &= b;
    }

    bool operator==(const footprint& a, const footprint& b) {
        for (uint i = 0; i < MAX_COMPONENTS; ++i)
            if (a[i] != b[i])
                return false;
        return true;
    }
    bool operator!=(const footprint& a, const footprint& b) {
        return !(a == b);
    }
}
