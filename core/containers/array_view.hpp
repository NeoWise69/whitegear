
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_ARRAY_VIEW_HPP
#define WHITEGEAR_ARRAY_VIEW_HPP

#include <core/typedefs.hpp>

#include <initializer_list>

namespace wg {
    template<class T>
    class array_view {
    public:
        using pointer_type = T*;
        using const_pointer_type = const T*;
        using reference_type = T&;
        using const_reference_type = const T&;
        using size_type = size_t;

        inline array_view(const array_view&) = default;
        inline array_view& operator=(const array_view&) = default;
        inline array_view(array_view&&) noexcept = default;
        inline array_view& operator=(array_view&&) noexcept = default;

        inline virtual ~array_view() = default;
        inline constexpr array_view() noexcept : mPtr(nullptr), mSize(0) {}
        inline constexpr array_view(pointer_type ptr, size_type size) noexcept : mPtr(ptr), mSize(size) {}
        inline constexpr array_view(const std::initializer_list<T>& list) noexcept : mPtr(list.begin()), mSize(list.size()) {}
        template<class It>
        inline constexpr array_view(It first, It last) noexcept : mPtr(first), mSize(last - first) {}
        template<>
        inline constexpr array_view(pointer_type first, pointer_type last) noexcept : mPtr(first), mSize(last - first) {}

        inline constexpr size_type size() const noexcept { return mSize; }
        inline constexpr pointer_type data() const noexcept { return mPtr; }
        inline constexpr bool empty() const noexcept { return mSize == 0 && !mPtr; }

        inline constexpr reference_type operator[](int i) { return *(mPtr + i); }
        inline constexpr const_reference_type operator[](int i) const { return *(mPtr + i); }

        inline constexpr pointer_type begin() noexcept { return pointer_type(mPtr); }
        inline constexpr pointer_type end() noexcept { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type begin() const noexcept { return pointer_type(mPtr); }
        inline constexpr const_pointer_type end() const noexcept { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type cbegin() const noexcept { return pointer_type(mPtr); }
        inline constexpr const_pointer_type cend() const noexcept { return pointer_type(mPtr + mSize); }
    private:
        const_pointer_type mPtr;
        size_type mSize;
    };
    template<class T>
    inline bool operator==(const array_view<T>& a, const array_view<T>& b) noexcept {
        if (a.size() != b.size()) return false;
        for (uint i = 0; i < a.size(); ++i) {
            if (a[i] != b[i])
                return false;
        }
        return true;
    }
    template<class T>
    inline bool operator!=(const array_view<T>& a, const array_view<T>& b) noexcept {
        return !(a == b);
    }
}

#endif //WHITEGEAR_ARRAY_VIEW_HPP
