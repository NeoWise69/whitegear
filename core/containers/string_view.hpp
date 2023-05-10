
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_STRING_VIEW_HPP
#define WHITEGEAR_STRING_VIEW_HPP

#include "array_view.hpp"
#include <cctype>
#include <string.h>

namespace wg {
    template<class Char = char>
    class string_view_base;

    using string_view = string_view_base<>;
    using wstring_view = string_view_base<wchar_t>;

    template<class Char>
    class string_view_base {
    public:
        using value_type = Char;
        using pointer_type = Char*;
        using const_pointer_type = const Char*;
        using reference_type = Char&;
        using const_reference_type = const Char&;
        using size_type = size_t;

        inline string_view_base(const string_view_base&) = default;
        inline string_view_base& operator=(const string_view_base&) = default;
        inline string_view_base(string_view_base&&) noexcept = default;
        inline string_view_base& operator=(string_view_base&&) noexcept = default;

        inline virtual ~string_view_base() = default;
        inline constexpr string_view_base() : mPtr(nullptr), mSize(0) {}
        inline constexpr string_view_base(const_pointer_type ptr, size_type size) : mPtr(ptr), mSize(size) {}
        inline constexpr string_view_base(pointer_type ptr) : mPtr(ptr), mSize(strlen(ptr)) {}
        inline constexpr string_view_base(const_pointer_type ptr) : mPtr(ptr), mSize(strlen(ptr)) {}
        inline constexpr string_view_base(const std::initializer_list<Char>& list) : mPtr(list.begin()), mSize(list.size()) {}
        template<class It>
        inline constexpr string_view_base(It first, It last) : mPtr(first), mSize(last - first) {}
        template<>
        inline constexpr string_view_base(pointer_type first, pointer_type last) : mPtr(first), mSize(last - first) {}

        inline constexpr size_type size() const { return mSize; }
        inline constexpr pointer_type data() const { return mPtr; }
        inline constexpr const_pointer_type c_str() const { return mPtr; }
        inline constexpr bool empty() const { return mSize == 0 && !mPtr; }

        inline constexpr reference_type operator[](int i) { return *(mPtr + i); }
        inline constexpr const_reference_type operator[](int i) const { return *(mPtr + i); }

        inline constexpr pointer_type begin() { return pointer_type(mPtr); }
        inline constexpr pointer_type end() { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type begin() const { return pointer_type(mPtr); }
        inline constexpr const_pointer_type end() const { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type cbegin() const { return pointer_type(mPtr); }
        inline constexpr const_pointer_type cend() const { return pointer_type(mPtr + mSize); }

        template<class U>
        inline static bool compare(const string_view_base<Char>& a, const string_view_base<U>& b) {
            if (a.size() != b.size()) return false;
            for (size_t i = 0; i < a.size(); ++i)
                if (a[i] != Char(b[i]))
                    return false;
            return true;
        }
        template<>
        inline static bool compare(const string_view_base<Char>& a, const string_view_base<Char>& b) {
            if (a.size() != b.size()) return false;
            return !strcmp(a.c_str(), b.c_str());
        }
        inline bool compare(const string_view_base<Char>& other) const {
            return string_view_base<Char>::compare(*this, other);
        }
        template<class U>
        inline bool compare(const string_view_base<U>& other) const {
            return string_view_base<Char>::compare(*this, other);
        }

        inline bool operator==(const string_view_base<Char>& other) const {
            return compare(other);
        }
        inline bool operator!=(const string_view_base<Char>& other) const {
            return !(*this == other);
        }
        inline static string_view_base to_lower(const string_view_base<Char>& other) {
            if (other.empty()) return {};
            string_view_base<Char> r = other;
            for (auto& c : r)
                c = Char(std::tolower(c));
            return r;
        }
        inline string_view_base& to_lower() {
            return *this = string_view_base<Char>::to_lower(*this);
        }
        inline static string_view_base to_upper(const string_view_base<Char>& other) {
            if (other.empty()) return {};
            string_view_base<Char> r = other;
            for (auto& c : r)
                c = Char(std::toupper(c));
            return r;
        }
        inline string_view_base& to_upper() {
            return *this = string_view_base<Char>::to_upper(*this);
        }
    private:
        const_pointer_type mPtr;
        size_type mSize;
    };
}

#endif //WHITEGEAR_STRING_VIEW_HPP
