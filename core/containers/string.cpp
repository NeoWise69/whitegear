
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/containers/string.hpp>
#include <cstring>
#include <new>
#include <cstdio>
#include <cctype>

namespace wg {
    namespace {
        const char lower_table[256] = {
                0000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
                0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
                0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
                0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
                0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
                0x78, 0x79, 0x7a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
                0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
                0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
                0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
        };
        const char upper_table[256] = {
                0000, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
                0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
                0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
                0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
                0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
                0x60, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
                0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
                0x58, 0x59, 0x5a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
        };
    }

    struct string_impl {
        uint use_count = 1;
        bool is_static = true;

        union {
            struct heap_data {
                char *ptr;
                u64 size;
                u64 cap;
            } large;
            struct static_data {
                char ptr[sizeof(heap_data)]{};
            } small = {};
        };

        inline string_impl() = default;
        inline string_impl(const string_impl& o) {
            is_static = o.is_static;
            if (is_static) {
                memcpy(small.ptr, o.small.ptr, 24);
            }
            else {
                auto& b = large;
                b.size = o.large.size;
                b.cap = o.large.cap;
                b.ptr = new char[b.cap + 1]{};
                memcpy(b.ptr, o.large.ptr, b.size);
            }
        }
        inline string_impl(const char* s, u64 len) {
            if (len > 24) {
                auto& b = large;
                if (len > b.cap) {
                    b.ptr = new char[len + 1]{};
                }
                else {
                    memset(b.ptr, 0, len + 1);
                }
                memcpy(b.ptr, s, len);
                b.size = len;
                b.cap = len;
                is_static = false;
            }
            else {
                memcpy(small.ptr, s, len);
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

    string::string() : mImpl(new string_impl()) {}

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

    string::string(const char *s) : mImpl(new string_impl(s, strlen(s))) {}

    string::string(const char *s, u64 len) : mImpl(new string_impl(s, len)) {}

    string &string::operator=(const char *s) {
        const auto len = strlen(s);
        if (mImpl) {
            if (mImpl->use_count > 1) {
                *this = clone();
            }
            // yeah, this is a simple solution, but rather slow :(
            // new(mImpl) string_impl(s, len);
            if (mImpl->is_static && len < 24) {
                memcpy(get_ptr(), s, len);
            }
            else if (mImpl->is_static && len >= 24) {
                const auto alloc_size = get_alloc_size(len + size());
                char* tmp = new char[alloc_size]{};
                memcpy(tmp, get_ptr(), size());
                memcpy(tmp + size(), s, len);
                mImpl->is_static = false;
                mImpl->large.ptr = tmp;
                mImpl->large.size = len;
                mImpl->large.cap = alloc_size;
            }
            else if (!mImpl->is_static && len < mImpl->large.cap) {
                memset(get_ptr(), 0, mImpl->large.cap);
                memcpy(get_ptr(), s, len);
                mImpl->large.size = len;
            }
            else if (!mImpl->is_static && len >= mImpl->large.cap) {
                const auto alloc_size = get_alloc_size(len + size());
                char* tmp = new char[alloc_size]{};
                memcpy(tmp, get_ptr(), mImpl->large.size);
                memcpy(tmp + mImpl->large.size, s, len);
                delete[] mImpl->large.ptr;
                mImpl->large.ptr = tmp;
                mImpl->large.size = len;
                mImpl->large.cap = alloc_size;
            }
        }
        else {
            mImpl = new string_impl(s, len);
        }
        return *this;
    }

    char *string::get_ptr() {
        if (mImpl && mImpl->is_static) {
            return (char*)mImpl->small.ptr;
        }
        return mImpl->large.ptr;
    }

    char *string::get_ptr() const {
        if (mImpl && mImpl->is_static) {
            return mImpl->small.ptr;
        }
        return mImpl->large.ptr;
    }

// TODO: update this to be more efficient!
    u64 string::get_size() const {
        return mImpl->is_static ? strlen(mImpl->small.ptr) : mImpl->large.size;
    }

    const u64 string::size() const {
        return get_size();
    }

    const char *string::c_str() const {
        return get_ptr();
    }

    char *string::data() const {
        return get_ptr();
    }

    char *string::begin() {
        return get_ptr();
    }

    const char *string::begin() const {
        return get_ptr();
    }

    char *string::end() {
        return get_ptr() + get_size();
    }

    const char *string::end() const {
        return get_ptr() + get_size();
    }

    string& string::append(const char c, u64 len) {
        if (mImpl->use_count > 1) {
            *this = clone();
        }

        if (mImpl->is_static) {
            const auto sz = size();
            if (len < (24 - sz)) {
                for (u64 i = sz; i < len + sz; ++i) {
                    mImpl->small.ptr[i] = c;
                }
            }
            else {
                const auto alloc_size = get_alloc_size(sz + len);
                char* tmp = new char[alloc_size]{};
                memcpy(tmp, get_ptr(), sz);
                for (u64 i = sz; i < sz + len; ++i) {
                    tmp[i] = c;
                }
                mImpl->large.ptr = tmp;
                mImpl->large.size = sz + len;
                mImpl->large.cap = alloc_size;
            }

            mImpl->is_static = false;
        }
        else {
            if (len < (size() - capacity())) {
                for (u64 i = size(); i < size() + len; ++i) {
                    mImpl->large.ptr[i] = c;
                }
            }
            else {
                const auto alloc_size = get_alloc_size(size() + len);
                char* tmp = new char[alloc_size]{};
                memcpy(tmp, get_ptr(), size());
                for (u64 i = size(); i < size() + len; ++i) {
                    tmp[i] = c;
                }
                mImpl->large.ptr = tmp;
                mImpl->large.size = size() + len;
                mImpl->large.cap = alloc_size;
            }
        }

        return *this;
    }

    bool string::empty() const {
        return !(mImpl && get_ptr() && get_size());
    }

    const u64 string::capacity() const {
        return mImpl->is_static ? 24 : mImpl->large.cap;
    }

    u64 string::get_alloc_size(u64 minimal) const {
        return u64(float(minimal) * 1.6f);
    }

    string& string::append(const char *s, u64 len) {
        if (mImpl->use_count > 1) {
            *this = clone();
        }

        if (mImpl->is_static) {
            const auto sz = size();
            if (len < (24 - sz)) {
                memcpy(mImpl->small.ptr + sz, s, len);
            }
            else {
                const auto alloc_size = get_alloc_size(sz + len);
                char* tmp = new char[alloc_size]{};
                memcpy(tmp, get_ptr(), sz);
                memcpy(tmp + sz, s, len);
                mImpl->large.ptr = tmp;
                mImpl->large.size = sz + len;
                mImpl->large.cap = alloc_size;
            }

            mImpl->is_static = false;
        }
        else {
            if (len < (size() - capacity())) {
                memcpy(mImpl->large.ptr + size(), s, len);
            }
            else {
                const auto alloc_size = get_alloc_size(size() + len);
                char* tmp = new char[alloc_size]{};
                memcpy(tmp, get_ptr(), size());
                memcpy(tmp + size(), s, len);
                mImpl->large.ptr = tmp;
                mImpl->large.size = size() + len;
                mImpl->large.cap = alloc_size;
            }
        }

        return *this;
    }

    string& string::append(const char *s) {
        append(s, strlen(s));
        return *this;
    }

    string& string::append(const string &o) {
        append(o.c_str(), o.size());
        return *this;
    }

    string& string::append(string &&o) {
        append(o.c_str(), o.size());
        return *this;
    }

    string &string::operator+=(const char *s) {
        return append(s);
    }

    string &string::operator+=(const char c) {
        return append(c);
    }

    string &string::operator+=(const string &o) {
        return append(o);
    }

    string &string::operator+=(string &&o) {
        return append(std::move(o));
    }

    bool string::compare(const char *s) const {
        if (!s) return false;
        const auto len = string::length(s);
        if (size() != len) return false;
        return !strncmp(c_str(), s, len);
    }

    u64 string::length(const char *s) {
        return strlen(s);
    }

    u64 string::length(const string &s) {
        return s.size();
    }

    bool string::compare(const char *s, u64 len) const {
        if (size() != len) return false;
        if (!s || len == 0) return false;
        return string::compare(c_str(), s);
    }

    bool string::compare(const string &s) const {
        return compare(s.c_str(), s.size());
    }

    bool string::compare(const char *a, const char *b) {
        return !strcmp(a, b);
    }

    char string::lower(const char c) {
        return lower_table[c];
    }

    char string::upper(const char c) {
        return upper_table[c];
    }

    string string::lower(const char *c) {
        string s(c);
        for (auto& ch : s) ch = lower_table[ch];
        return s;
    }

    string string::lower(const char *c, u64 len) {
        string s(c, len);
        for (auto& ch : s) ch = lower_table[ch];
        return s;
    }

    string string::upper(const char *c) {
        string s(c);
        for (auto& ch : s) ch = upper_table[ch];
        return s;
    }

    string string::upper(const char *c, u64 len) {
        string s(c, len);
        for (auto& ch : s) ch = upper_table[ch];
        return s;
    }

    string operator+(const string& a, const string& b) {
        return string(a) += b;
    }

    string operator+(const string& a, const char& b) {
        return string(a) += b;
    }

    string operator+(const string& a, const char* b) {
        return string(a) += b;
    }

    string stringify(i8  v) {
        return &v;
    }

    string stringify(u8  v) {
        return (char*)&v;
    }

    string stringify(i16 v) {
        char buf[5]{};
        sprintf_s(buf, "%d", v);
        return { buf, 5 };
    }

    string stringify(u16 v) {
        char buf[5]{};
        sprintf_s(buf, "%d", v);
        return { buf, 5 };
    }

    string stringify(i32 v) {
        char buf[10]{};
        sprintf_s(buf, "%d", v);
        return { buf, 10 };
    }

    string stringify(u32 v) {
        char buf[10]{};
        sprintf_s(buf, "%d", v);
        return { buf, 10 };
    }

    string stringify(i64 v) {
        char buf[19]{};
        sprintf_s(buf, "%lli", v);
        return { buf, 19 };
    }

    string stringify(u64 v) {
        char buf[19]{};
        sprintf_s(buf, "%llu", v);
        return { buf, 19 };
    }

    string stringify(float v) {
        char buf[10]{};
        sprintf_s(buf, "%f", v);
        return { buf, 23 };
    }

    string stringify(double v) {
        char buf[20]{};
        sprintf_s(buf, "%f", v);
        return { buf, 23 };
    }


}
