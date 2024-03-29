
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
#include <cstring>

namespace wg {
    template<class Char = char>
    class string_view_base;

    using string_view = string_view_base<char>;
    using wstring_view = string_view_base<wchar_t>;

    template<class Char>
    class string_view_base {
    public:
        using value_type = Char;
        using pointer_type = Char*;
        using const_pointer_type = const Char*;
        using reference_type = Char&;
        using const_reference_type = const Char&;
        using size_type = uint;

        inline string_view_base(const string_view_base&) = default;
        inline string_view_base& operator=(const string_view_base&) = default;
        inline string_view_base(string_view_base&&) noexcept = default;
        inline string_view_base& operator=(string_view_base&&) noexcept = default;

        inline virtual ~string_view_base() noexcept = default;
        inline constexpr string_view_base() noexcept : mPtr(nullptr), mSize(0) {}
        inline constexpr string_view_base(const_pointer_type ptr, size_type size) noexcept : mPtr(ptr), mSize(size) {}
        inline constexpr string_view_base(pointer_type ptr) noexcept : mPtr(ptr), mSize(uint(strlen(ptr))) {}
        inline constexpr string_view_base(const_pointer_type ptr) noexcept : mPtr(ptr), mSize(uint(strlen(ptr))) {}
        inline constexpr string_view_base(const std::initializer_list<Char>& list) noexcept : mPtr(list.begin()), mSize(list.size()) {}
        template<class It>
        inline constexpr string_view_base(It first, It last) noexcept : mPtr(first), mSize(last - first) {}
        template<>
        inline constexpr string_view_base(pointer_type first, pointer_type last) noexcept : mPtr(first), mSize(last - first) {}

        inline constexpr size_type size() const noexcept { return mSize; }
        inline constexpr pointer_type data() const noexcept { return mPtr; }
        inline constexpr const_pointer_type c_str() const noexcept { return mPtr; }
        inline constexpr bool empty() const noexcept { return mSize == 0 && !mPtr; }

        inline constexpr reference_type operator[](int i) { return *(mPtr + i); }
        inline constexpr const_reference_type operator[](int i) const { return *(mPtr + i); }

        inline constexpr pointer_type begin() noexcept { return pointer_type(mPtr); }
        inline constexpr pointer_type end() noexcept { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type begin() const noexcept { return pointer_type(mPtr); }
        inline constexpr const_pointer_type end() const noexcept { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type cbegin() const noexcept { return pointer_type(mPtr); }
        inline constexpr const_pointer_type cend() const noexcept { return pointer_type(mPtr + mSize); }

        template<class U>
        inline static bool compare(const string_view_base<Char>& a, const string_view_base<U>& b) noexcept {
            if (a.size() != b.size()) return false;
            for (size_t i = 0; i < a.size(); ++i)
                if (a[i] != Char(b[i]))
                    return false;
            return true;
        }
        template<>
        inline static bool compare(const string_view_base<Char>& a, const string_view_base<Char>& b) noexcept {
            if (a.size() != b.size()) return false;
            return !strcmp(a.c_str(), b.c_str());
        }
        inline bool compare(const string_view_base<Char>& other) const noexcept {
            return string_view_base<Char>::compare(*this, other);
        }
        template<class U>
        inline bool compare(const string_view_base<U>& other) const noexcept {
            return string_view_base<Char>::compare(*this, other);
        }

        inline bool operator==(const string_view_base<Char>& other) const noexcept {
            return compare(other);
        }
        inline bool operator!=(const string_view_base<Char>& other) const noexcept {
            return !(*this == other);
        }
        inline static string_view_base to_lower(const string_view_base<Char>& other) noexcept {
            if (other.empty()) return {};
            string_view_base<Char> r = other;
            for (auto& c : r)
                c = Char(std::tolower(c));
            return r;
        }
        inline string_view_base& to_lower() noexcept {
            return *this = string_view_base<Char>::to_lower(*this);
        }
        inline static string_view_base to_upper(const string_view_base<Char>& other) noexcept {
            if (other.empty()) return {};
            string_view_base<Char> r = other;
            for (auto& c : r)
                c = Char(std::toupper(c));
            return r;
        }
        inline string_view_base& to_upper() noexcept {
            return *this = string_view_base<Char>::to_upper(*this);
        }
    private:
        const_pointer_type mPtr;
        size_type mSize;
    };
}

#endif //WHITEGEAR_STRING_VIEW_HPP
