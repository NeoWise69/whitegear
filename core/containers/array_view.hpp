
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
        inline constexpr array_view() : mPtr(nullptr), mSize(0) {}
        inline constexpr array_view(pointer_type ptr, size_type size) : mPtr(ptr), mSize(size) {}
        inline constexpr array_view(const std::initializer_list<T>& list) : mPtr(list.begin()), mSize(list.size()) {}
        template<class It>
        inline constexpr array_view(It first, It last) : mPtr(first), mSize(last - first) {}
        template<>
        inline constexpr array_view(pointer_type first, pointer_type last) : mPtr(first), mSize(last - first) {}

        inline constexpr size_type size() const { return mSize; }
        inline constexpr pointer_type data() const { return mPtr; }
        inline constexpr bool empty() const { return mSize == 0 && !mPtr; }

        inline constexpr reference_type operator[](int i) { return *(mPtr + i); }
        inline constexpr const_reference_type operator[](int i) const { return *(mPtr + i); }

        inline constexpr pointer_type begin() { return pointer_type(mPtr); }
        inline constexpr pointer_type end() { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type begin() const { return pointer_type(mPtr); }
        inline constexpr const_pointer_type end() const { return pointer_type(mPtr + mSize); }
        inline constexpr const_pointer_type cbegin() const { return pointer_type(mPtr); }
        inline constexpr const_pointer_type cend() const { return pointer_type(mPtr + mSize); }
    private:
        const_pointer_type mPtr;
        size_type mSize;
    };
}

#endif //WHITEGEAR_ARRAY_VIEW_HPP
