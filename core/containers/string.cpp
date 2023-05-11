
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/containers/string.hpp>
#include <cstring>

namespace wg {
    struct string_impl {
        uint use_count = 0;
        bool is_static = true;

        struct heap_data {
            char* ptr;
            u64 size;
            u64 cap;
        };
        struct static_data {
            char ptr[sizeof(heap_data)]{};
        };

        union {
            heap_data large;
            static_data small = {};
        };

        inline string_impl(uint use) : use_count(use) {}
        inline string_impl(const string_impl& o) {
            is_static = o.is_static;
            if (is_static) {
                memcpy(small.ptr, o.small.ptr, sizeof(heap_data));
            }
            else {
                auto& b = large;
                b.size = o.large.size;
                b.cap = o.large.cap;
                b.ptr = new char[b.cap]{};
                memcpy(b.ptr, o.large.ptr, b.size);
            }
        }
};

    string::~string() {
        --mImpl->use_count;
        if (mImpl->use_count == 0) {
            if (!mImpl->is_static) {
                delete[] mImpl->large.ptr;
            }
            delete mImpl;
        }
    }

    string::string(const string &o) : mImpl(o.mImpl) {
        ++mImpl->use_count;
    }

    string::string(string &&o) noexcept : mImpl(o.mImpl) {
        ++mImpl->use_count;
    }

    string::string() : mImpl(new string_impl(1)) {}

    string &string::operator=(const string &o) {
        mImpl = o.mImpl;
        ++mImpl->use_count;
        return *this;
    }

    string &string::operator=(string &&o) noexcept {
        mImpl = o.mImpl;
        ++mImpl->use_count;
        return *this;
    }

    const char &string::operator[](i64 i) const {
        return mImpl->is_static ? mImpl->small.ptr[i] : mImpl->large.ptr[i];
    }

    char &string::operator[](i64 i) {
        if (mImpl->use_count > 1) {
            *this = clone();
        }
        return mImpl->is_static ? mImpl->small.ptr[i] : mImpl->large.ptr[i];
    }

    string string::clone() const {
        return string(new string_impl(*mImpl));
    }

    string::string(string_impl * impl) : mImpl(impl) {}


}
