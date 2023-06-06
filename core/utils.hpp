
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_UTILS_HPP
#define WHITEGEAR_UTILS_HPP

#include <core/typedefs.hpp>
#include <type_traits>

namespace wg {
    /**
     * Returns lower between parameters
     */
    template<class A>
    inline constexpr A min(A x) {
        return x;
    }
    /**
     * Returns lower between parameters
     */
    template<class A, class B>
    inline constexpr A min(A x, B y) {
        return (x < B(y)) ? x : B(y);
    }
    /**
     * Returns lower between parameters
     */
    template<class A, class B, class C>
    inline constexpr A min(A x, B y, C z) {
        return min(min(x, y), z);
    }
    /**
     * Returns lower between parameters
     */
    template<class A, class B, class C, class D>
    inline constexpr A min(A x, B y, C z, D w) {
        return min(min(x, y), min(z, w));
    }
    /**
     * Returns higher between parameters
     */
    template<class A>
    inline constexpr A max(A x) {
        return x;
    }
    /**
     * Returns higher between parameters
     */
    template<class A, class B>
    inline constexpr A max(A x, B y) {
        return (x > B(y)) ? x : B(y);
    }
    /**
     * Returns higher between parameters
     */
    template<class A, class B, class C>
    inline constexpr A max(A x, B y, C z) {
        return max(max(x, y), z);
    }
    /**
     * Returns higher between parameters
     */
    template<class A, class B, class C, class D>
    inline constexpr A max(A x, B y, C z, D w) {
        return max(max(x, y), max(z, w));
    }
    /**
     * Swap utility
     */
    template<class T>
    inline void swap(T& a, T& b) {
        T t = a;
        a = b;
        b = t;
    }
    template<class F, class S>
    struct pair {
        inline pair() {}
        inline pair(const F& f, const S& s)
            : first(f), second(s)
        {}
        F first;
        S second;
    };

    template<class F, class S>
    inline bool operator==(const pair<F, S>& a, const pair<F, S>& b) {
        return
                a.first == b.first &&
                a.second == b.second
            ;
    }
    template<class F, class S>
    inline bool operator!=(const pair<F, S>& a, const pair<F, S>& b) {
        return !(
                a.first == b.first &&
                a.second == b.second
            );
    }
    template<class F, class S>
    inline bool operator<(const pair<F, S>& a, const pair<F, S>& b) {
        if (a.first < b.first) return true;
        if (a.first != b.first) return false;
        return a.second < b.second;
    }
    template<class F, class S>
    inline bool operator>(const pair<F, S>& a, const pair<F, S>& b) {
        if (a.first > b.first) return true;
        if (a.first != b.first) return false;
        return a.second > b.second;
    }

    template<class F, class S>
    inline pair<F, S> make_pair(const F& f, const S& s) {
        return pair<F, S>(f, s);
    }

    template<class T>
    inline T begin(pair<T, T>& r) { return r.first; }
    template<class T>
    inline T end(pair<T, T>& r) { return r.second; }
    template<class T>
    inline T begin(const pair<T, T>& r) { return r.first; }
    template<class T>
    inline T end(const pair<T, T>& r) { return r.second; }

    /**
     * Templated comparator.
     */
    template<class T>
    struct compare {
        inline static bool less(const T& a, const T& b) { return a < b; }
        inline static bool greater(const T& a, const T& b) { return a > b; }
        inline static bool equal(const T& a, const T& b) { return a == b; }
        inline static bool nequal(const T& a, const T& b) { return a != b; }
    };
    template<class T>
    struct compare<T*> {
        inline static bool less(const T* a, const T* b) { return a < b; }
        inline static bool greater(const T* a, const T* b) { return a > b; }
        inline static bool equal(const T* a, const T* b) { return a == b; }
        inline static bool nequal(const T* a, const T* b) { return a != b; }
    };
}

#endif //WHITEGEAR_UTILS_HPP
