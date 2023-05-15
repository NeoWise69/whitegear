
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

/**
 * Bounded array is a bit tweaked static C-style array [].
 * It has additional counter to keep track of array's state.
 */

#ifndef WHITEGEAR_BOUNDED_ARRAY_HPP
#define WHITEGEAR_BOUNDED_ARRAY_HPP

#include <core/typedefs.hpp>

#include <type_traits> // std::forward, std::is_pod_v
#include <initializer_list> // std::initializer_list
#include <cassert> // assert
#include <new> // placement new

namespace wg {
    /**
* Storage is a simple contiguous array of bytes,
* that splits between 'spawned' objects. This require
* NO allocations, what means -> there're ZERO heap usage
* at least for array needs. All required space reserved
* here at first instantiation time.
*/
    template<class T, uint N>
    class bounded_array_storage {
    protected:
        bounded_array_storage() = default;
        virtual ~bounded_array_storage() = default;
        /**
        * Gets access to already constructed piece of data.
        * Otherwise, UB and UR.
        * (undefined behaviour and unexpected results)
        */
        inline T* get_type_data(uint index) const {
            assert(N >= index && "Index out of bounds!");
            return (T*)(mRaw + (sizeof(T) * index));
        }
        /**
        * Performs same operation that get_type_data(i) did,
        * but it also constructs an object instance inside
        * reserved memory chunk.
        * [OPTIONAL] Accepts arguments for constructor.
        */
        template<class...Args>
        inline T* new_type_data(uint index, Args&&...args) const {
            assert(N > index && "Index out of bounds!");
            T* const p = (T*)(mRaw + (sizeof(T) * index));
            new (p) T(std::forward<Args>(args)...);
            return p;
        }
        /**
        * Deconstruct non-POD object types by calling destructor,
        * and release POD types just by setting it to ZERO.
        */
        inline void deconstruct_data_at(uint index) {
            assert(N > index && "Index out of bounds!");
            T* const p = (T*)(mRaw + (sizeof(T) * index));
            if constexpr (std::is_pod_v<T>) {
                *p = T{};
            }
            else {
                p->~T();
            }
        }

    private:
        // Simple contiguous memory.
        char mRaw[sizeof(T) * N]{};
    };

/**
* bounded_array - simple static array, but with
* a couple of small tweaks. e.g.: it has an index
* to last added(constructed) member. Also it requires
* NO(ZERO) allocations to work with ANY types of objects.
* Provides usable and simple interfaces.
* Supports both emplacing(emplace) and removing(pop).
*/
    template<class T, uint N>
    class bounded_array : public bounded_array_storage<T, N> {
    public:
        using storage = bounded_array_storage<T, N>;

        inline bounded_array() = default;
        virtual ~bounded_array() {
            for (uint i = 0; i < mSize; ++i)
                storage::deconstruct_data_at(i);
        }

        inline bounded_array(std::initializer_list<T> list) {
            for (auto e : list) {
                emplace_back(e);
            }
        }

        template<class...Args>
        inline explicit bounded_array(uint num, Args&&...args) {
            for (uint i = 0; i < num; ++i)
                emplace_back(std::forward<Args>(args)...);
        }

        inline bounded_array(const bounded_array&) = delete;
        inline bounded_array& operator=(const bounded_array&) = delete;
        inline bounded_array(bounded_array&&) noexcept = delete;
        inline bounded_array& operator=(bounded_array&&) noexcept = delete;

        inline auto begin() { return storage::get_type_data(0); }
        inline auto end() { return storage::get_type_data(mSize); }
        inline const auto begin() const { return storage::get_type_data(0); }
        inline const auto end() const { return storage::get_type_data(mSize); }
        inline const auto cbegin() const { return storage::get_type_data(0); }
        inline const auto cend() const { return storage::get_type_data(mSize); }

        template<class...Args>
        inline T* emplace_back(Args&&...args) {
            assert(N > mSize && "Bounded array has a BOUNDS, isn't it? You get out of it!");
            return storage::new_type_data(mSize++, std::forward<Args>(args)...);
        }

        inline void erase_back() {
            storage::deconstruct_data_at(--mSize);
        }

        inline void pop_back() { erase_back(); }

        inline auto size() const { return mSize; }
        inline constexpr auto capacity() const { return N; }
        inline bool empty() const { return mSize == 0; }

        inline auto data() const { return storage::get_type_data(0); }
        inline auto at(uint i) { return storage::get_type_data(i); }
        inline auto at(uint i) const { return storage::get_type_data(i); }

        inline auto operator[](uint i) { return at(i); }
        inline auto operator[](uint i) const { return at(i); }

    private:
        uint mSize = {};
    };
}

#endif //WHITEGEAR_BOUNDED_ARRAY_HPP
