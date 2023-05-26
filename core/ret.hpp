
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RET_HPP
#define WHITEGEAR_RET_HPP

#include <core/containers/string.hpp>

namespace wg {
/**
     * Simple wrapper around return value.
     * Can produce a formatted message(info).
     */
    template<class T>
    class ret_t {
    public:
        inline ret_t(T v) : mValue(v), mReceived(false) {}
        inline ret_t() = default;
        inline ~ret_t() {}

        inline ret_t(const ret_t& o) : mValue(o.mValue), mReceived(true) {}
        inline ret_t(ret_t&& o) noexcept : mValue(o.mValue), mReceived(true) {}
        inline ret_t& operator=(const ret_t& o) { mValue = o.mValue; mReceived = true; return *this; }
        inline ret_t& operator=(ret_t&& o) noexcept { mValue = o.mValue; mReceived = true; return *this; }

        inline string get_error_name() const { return {}; }
        inline string get_error_desc() const { return {}; }

        inline bool is_ok() const { return false; }
        inline operator bool() const { return is_ok(); }
        inline auto operator*() const { return mValue; }
        inline operator T() const { return mValue; }
    private:
        T mValue = {};
        mutable bool mReceived = false;
    };
}

#endif //WHITEGEAR_RET_HPP
