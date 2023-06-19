
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
#include <limits>

namespace wg {
    /**
     * Returns lower between parameters
     */
    template<class A>
    inline constexpr A min(A x) noexcept {
        return x;
    }
    /**
     * Returns lower between parameters
     */
    template<class A, class B>
    inline constexpr A min(A x, B y) noexcept {
        return (x < B(y)) ? x : B(y);
    }
    /**
     * Returns lower between parameters
     */
    template<class A, class B, class C>
    inline constexpr A min(A x, B y, C z) noexcept {
        return min(min(x, y), z);
    }
    /**
     * Returns lower between parameters
     */
    template<class A, class B, class C, class D>
    inline constexpr A min(A x, B y, C z, D w) noexcept {
        return min(min(x, y), min(z, w));
    }
    /**
     * Returns higher between parameters
     */
    template<class A>
    inline constexpr A max(A x) noexcept {
        return x;
    }
    /**
     * Returns higher between parameters
     */
    template<class A, class B>
    inline constexpr A max(A x, B y) noexcept {
        return (x > B(y)) ? x : B(y);
    }
    /**
     * Returns higher between parameters
     */
    template<class A, class B, class C>
    inline constexpr A max(A x, B y, C z) noexcept {
        return max(max(x, y), z);
    }
    /**
     * Returns higher between parameters
     */
    template<class A, class B, class C, class D>
    inline constexpr A max(A x, B y, C z, D w) noexcept {
        return max(max(x, y), max(z, w));
    }


    template<class F, class S>
    struct pair {
        inline pair() noexcept {}
        inline pair(const F& f, const S& s) noexcept
            : first(f), second(s)
        {}
        F first;
        S second;
    };
    template<class F, class S>
    inline bool operator==(const pair<F, S>& a, const pair<F, S>& b) noexcept {
        return
                a.first == b.first &&
                a.second == b.second
            ;
    }
    template<class F, class S>
    inline bool operator!=(const pair<F, S>& a, const pair<F, S>& b) noexcept {
        return !(
                a.first == b.first &&
                a.second == b.second
            );
    }
    template<class F, class S>
    inline bool operator<(const pair<F, S>& a, const pair<F, S>& b) noexcept {
        if (a.first < b.first) return true;
        if (a.first != b.first) return false;
        return a.second < b.second;
    }
    template<class F, class S>
    inline bool operator>(const pair<F, S>& a, const pair<F, S>& b) noexcept {
        if (a.first > b.first) return true;
        if (a.first != b.first) return false;
        return a.second > b.second;
    }

    template<class F, class S>
    inline pair<F, S> make_pair(const F& f, const S& s) noexcept {
        return pair<F, S>(f, s);
    }

    template<class T>
    inline T begin(pair<T, T>& r) noexcept { return r.first; }
    template<class T>
    inline T end(pair<T, T>& r) noexcept { return r.second; }
    template<class T>
    inline T begin(const pair<T, T>& r) noexcept { return r.first; }
    template<class T>
    inline T end(const pair<T, T>& r) noexcept { return r.second; }

    /**
     * Templated comparator.
     */
    template<class T>
    struct compare {
        inline static bool less(const T& a, const T& b) noexcept { return a < b; }
        inline static bool greater(const T& a, const T& b) noexcept { return a > b; }
        inline static bool equal(const T& a, const T& b) noexcept { return a == b; }
        inline static bool nequal(const T& a, const T& b) noexcept { return a != b; }
    };
    template<class T>
    struct compare<T*> {
        inline static bool less(const T* a, const T* b) noexcept { return a < b; }
        inline static bool greater(const T* a, const T* b) noexcept { return a > b; }
        inline static bool equal(const T* a, const T* b) noexcept { return a == b; }
        inline static bool nequal(const T* a, const T* b) noexcept { return a != b; }
    };

    /**
     * Swap utility
     */
    template<class T>
    inline void swap(T& a, T& b) noexcept {
        T t = std::move(a);
        a = std::move(b);
        b = std::move(t);
    }
    /**
     * Base class for random engine.
     */
    template<class NUM_TYPE,
            size_t W, size_t N, size_t M, size_t R,
            NUM_TYPE A, NUM_TYPE U, NUM_TYPE D, NUM_TYPE S,
            NUM_TYPE B, NUM_TYPE T,
            NUM_TYPE C, NUM_TYPE L, NUM_TYPE F>
    class random_engine_base {
    public:
        inline constexpr random_engine_base() noexcept { seed(); }
        inline constexpr random_engine_base(NUM_TYPE s) noexcept { seed(s); }

        inline constexpr void seed(NUM_TYPE value) {
            const auto mask = max();
            state[0] = value & mask;
            i = 1;
            do {
                state[i] = (init_mul * (state[i - 1] ^ (state[i - 1] >> (word_size - 2))) + i) & mask;
            } while (++i < state_size);
        }
        inline constexpr void seed() { seed(default_seed); }

        inline static constexpr NUM_TYPE min() { return 0; }
        inline static constexpr NUM_TYPE max() {
            return std::numeric_limits<NUM_TYPE>::max();
        }

        inline constexpr NUM_TYPE operator()() {
            if (i == state_size) twist();
            auto z = state[i];
            ++i;
            z ^= ((z >> tempering_u) & tempering_d);
            z ^= ((z << tempering_s) & tempering_b);
            z ^= ((z << tempering_t) & tempering_c);
            z ^= (z >> tempering_l);
            return z;
        }
        inline constexpr NUM_TYPE operator()(NUM_TYPE maximum) {
            if (i == state_size) twist();
            auto z = state[i];
            ++i;
            z ^= ((z >> tempering_u) & tempering_d);
            z ^= ((z << tempering_s) & tempering_b);
            z ^= ((z << tempering_t) & tempering_c);
            z ^= (z >> tempering_l);
            return z % maximum;
        }
    private:
        inline constexpr static NUM_TYPE word_size = W;
        inline constexpr static NUM_TYPE state_size = N;
        inline constexpr static NUM_TYPE shift_size = M;
        inline constexpr static NUM_TYPE mask_size = R;
        inline constexpr static NUM_TYPE xor_mask = A;
        inline constexpr static NUM_TYPE tempering_u = U;
        inline constexpr static NUM_TYPE tempering_d = D;
        inline constexpr static NUM_TYPE tempering_s = S;
        inline constexpr static NUM_TYPE tempering_b = B;
        inline constexpr static NUM_TYPE tempering_t = T;
        inline constexpr static NUM_TYPE tempering_c = C;
        inline constexpr static NUM_TYPE tempering_l = L;
        inline constexpr static NUM_TYPE init_mul = F;
        inline constexpr static NUM_TYPE default_seed = 0x1571;

        inline constexpr void twist() {
            const auto umask = (~NUM_TYPE(0)) << mask_size;
            const auto lmask = ~umask;
            const auto unroll_fac = 6ull;
            const auto unroll_extra1 = (state_size - shift_size) % unroll_fac;
            const auto unroll_extra2 = (shift_size - 1) % unroll_fac;
            auto j = 0ull;
            // split loop to avoid costly modulo operations
            do {
                const auto y = (state[j] & umask) | (state[j + 1] & lmask);
                state[j] = state[j + shift_size] ^ (y >> 1) ^ ((state[j + 1] & 1) * xor_mask);
            } while (++j < state_size - shift_size - unroll_extra1);
            do {
                const auto y = (state[j] & umask) | (state[j + 1] & lmask);
                state[j] = state[j + shift_size] ^ (y >> 1) ^ ((state[j + 1] & 1) * xor_mask);
            } while (++j < state_size - shift_size);
            do {
                const auto y = (state[j] & umask) | (state[j + 1] & lmask);
                state[j] = state[j - (state_size - shift_size)] ^ (y >> 1) ^ ((state[j + 1] & 1) * xor_mask);
            } while (++j < state_size - 1 - unroll_extra2);
            do {
                const auto y = (state[j] & umask) | (state[j + 1] & lmask);
                state[j] = state[j - (state_size - shift_size)] ^ (y >> 1) ^ ((state[j + 1] & 1) * xor_mask);
            } while (++j < state_size - 1);
            // last iteration
            const auto y = (state[state_size - 1] & umask) | (state[0] & lmask);
            state[state_size - 1] = state[shift_size - 1] ^ (y >> 1) ^ ((state[0] & 1) * xor_mask);
            i = 0;
        }

        NUM_TYPE state[state_size] = {};
        NUM_TYPE i = {};
    };

    /**
     * Mersenne-Twister based random engine implementation
     * with BOOST recommended predefined constants.
     */
    using random_engine = random_engine_base<uint64_t,
            64, 312, 156, 31,
            0xb5026f5aa96619e9, 29, 0x5555555555555555, 17,
            0x71d67fffeda60000, 37,
            0xfff7eee000000000, 43, 6364136223846793005>;
}

#endif //WHITEGEAR_UTILS_DX11_HPP
