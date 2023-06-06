
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_SMART_PTR_HPP
#define WHITEGEAR_SMART_PTR_HPP

#include <core/typedefs.hpp>
#include <core/ref_counted.hpp>

#include <memory>

namespace wg {
    /**
     * Container for reference counted object.
     * Keeps track of pointer lifetime.
     */
    template<class T>
    class ref_ptr {
    public:
        inline ref_ptr() = default;
        inline ref_ptr(std::nullptr_t) : ref_ptr() {}
        inline ref_ptr(const ref_ptr& rp) : ptr(rp.ptr) {
            inc_ref();
        }
        template<class U>
        inline ref_ptr(const ref_ptr<U>& rp) : ptr((T*)rp.ptr) {
            inc_ref();
        }
        inline explicit ref_ptr(T* p) : ptr(p) {
            inc_ref();
        }
        inline ~ref_ptr() {
            dec_ref();
        }
        inline ref_ptr& operator=(const ref_ptr& rp) {
            if (ptr != rp.ptr) {
                dec_ref();
                ptr = rp.ptr;
                inc_ref();
            }
            return *this;
        }
        template<class U>
        inline ref_ptr& operator=(const ref_ptr<U>& rp) {
            if (ptr != rp.ptr) {
                dec_ref();
                ptr = (T*)rp.ptr;
                inc_ref();
            }
            return *this;
        }
        inline ref_ptr& operator=(T* p) {
            if (ptr != p) {
                dec_ref();
                ptr = p;
                inc_ref();
            }
            return *this;
        }

        inline const T* operator->() const {
            return ptr;
        }

        inline T* operator->() {
            return ptr;
        }

        inline const T& operator*() const {
            return *ptr;
        }

        inline T& operator*() {
            return *ptr;
        }

        inline const T& operator[](i32 i) const {
            return ptr[i];
        }

        inline T& operator[](i32 i) {
            return ptr[i];
        }

        inline operator T*() const {
            return ptr;
        }

        inline void reset() {
            dec_ref();
        }

        inline T* release() {
            T* p = ptr;
            if (ptr) {
                ref_count* rc = get_ref_count_ptr();
                ++(rc->refs);
                reset();
                --(rc->refs);
            }
            return p;
        }

        inline bool is_empty() const {
            return ptr == nullptr;
        }

        inline T* get() const {
            return ptr;
        }

        inline i32 get_num_refs() const {
            return ptr ? ptr->get_num_refs() : 0;
        }

        inline i32 get_num_weaks() const {
            return ptr ? ptr->get_num_weaks() : 0;
        }

        inline ref_count* get_ref_count_ptr() const {
            return ptr ? ptr->get_ref_count_ptr() : (ref_count*)nullptr;
        }

    private:
        template<class>
        friend class ref_ptr;

        inline void inc_ref() {
            if (ptr) {
                ptr->inc_ref();
            }
        }
        inline void dec_ref() {
            if (ptr) {
                ptr->dec_ref();
                ptr = nullptr;
            }
        }

        T* ptr = nullptr;
    };

    template<class T, class...Args>
    inline ref_ptr<T> make_ref(Args&&...args) {
        return ref_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<class T, class U>
    inline ref_ptr<T> static_pointer_cast(const ref_ptr<U>& wp) {
        return ref_ptr<T>(static_cast<T*>(wp.get()));
    }

    template<class T, class U>
    inline ref_ptr<T> dynamic_pointer_cast(const ref_ptr<U>& wp) {
        return ref_ptr<T>(dynamic_cast<T*>(wp.get()));
    }

    template<class T>
    inline bool operator<(const ref_ptr<T>& a, const ref_ptr<T>& b) {
        return compare<T*>::less(a.get(), b.get());
    }
    template<class T>
    inline bool operator==(const ref_ptr<T>& a, const ref_ptr<T>& b) {
        return compare<T*>::equal(a.get(), b.get());
    }
    template<class T>
    inline bool operator!=(const ref_ptr<T>& a, const ref_ptr<T>& b) {
        return compare<T*>::nequal(a.get(), b.get());
    }


    template<class T>
    class weak_ptr {
    public:
        inline weak_ptr() = default;
        inline weak_ptr(std::nullptr_t) : weak_ptr() {}
        inline weak_ptr(const weak_ptr& wp) : ptr(wp.ptr), rc(wp.rc) {
            inc_ref();
        }
        template<class U>
        inline weak_ptr(const weak_ptr<U>& wp) : ptr((T*)wp.ptr), rc(wp.rc) {
            inc_ref();
        }
        inline weak_ptr(const ref_ptr<T>& rp) : ptr(rp.get()), rc(rp.get_ref_count_ptr()) {
            inc_ref();
        }
        inline explicit weak_ptr(T* p) : ptr(p), rc(ptr ? ptr->get_ref_count_ptr() : (ref_count*)nullptr)
        {
            inc_ref();
        }
        inline ~weak_ptr() { dec_ref(); }

        inline weak_ptr& operator=(const ref_ptr<T>& rp) {
            if (!(ptr == rp.get() && rc == rp.get_ref_count_ptr())) {
                dec_ref();
                ptr = rp.get();
                rc = rp.get_ref_count_ptr();
                inc_ref();
            }
            return *this;
        }
        inline weak_ptr& operator=(const weak_ptr& wp) {
            if (!(ptr == wp.ptr && rc == wp.rc)) {
                dec_ref();
                ptr = wp.ptr;
                rc = wp.rc;
                inc_ref();
            }
            return *this;
        }
        template<class U>
        inline weak_ptr& operator=(const weak_ptr<U>& wp) {
            if (!(ptr == (T*)(wp.ptr) && rc == wp.rc)) {
                dec_ref();
                ptr = (T*)wp.ptr;
                rc = wp.rc;
                inc_ref();
            }
            return *this;
        }
        inline weak_ptr& operator=(T* p) {
            ref_count* r = ptr ? ptr->get_ref_count_ptr() : (ref_count*)nullptr;
            if (!(ptr == p && rc == r)) {
                dec_ref();
                ptr = p;
                rc = r;
                inc_ref();
            }
            return *this;
        }

        inline ref_ptr<T> to_ref() const {
            return ref_ptr<T>((!is_expired()) ? ptr : (T*)nullptr);
        }

        inline T* get() const {
            return !is_expired() ? ptr : (T*)nullptr;
        }
        inline T* operator->() const {
            return get();
        }
        inline T& operator*() const {
            return *get();
        }
        inline T& operator[](i32 i) {
            return (*get())[i];
        }
        inline operator T*() const {
            return get();
        }
        inline void reset() {
            dec_ref();
        }
        inline bool empty() const {
            return rc == nullptr;
        }
        inline auto get_num_refs() const {
            return (rc && rc->refs >= 0) ? rc->refs : 0;
        }
        inline auto get_num_weak_refs() const {
            if (!is_expired())
                return ptr->get_num_weaks();
            return rc ? rc->weak_refs : 0;
        }
        inline bool is_expired() const {
            return rc ? rc->refs < 0 : true;
        }
        inline ref_count* get_ref_count_ptr() const {
            return rc;
        }
    private:
        template<class U>
        friend class weak_ptr;

        inline void inc_ref() {
            if (rc) {
                assert(rc->weak_refs >= 0);
                ++(rc->weak_refs);
            }
        }
        inline void dec_ref() {
            if (rc) {
                assert(rc->weak_refs > 0);
                --(rc->weak_refs);

                if (is_expired() && !(rc->weak_refs)) {
                    delete rc;
                }
            }
            ptr = nullptr;
            rc = nullptr;
        }

        T* ptr = nullptr;
        ref_count* rc = nullptr;
    };

    template<class T, class U>
    inline weak_ptr<T> static_pointer_cast(const weak_ptr<U>& wp) {
        return weak_ptr<T>(static_cast<T*>(wp.get()));
    }

    template<class T, class U>
    inline weak_ptr<T> dynamic_pointer_cast(const weak_ptr<U>& wp) {
        return weak_ptr<T>(dynamic_cast<T*>(wp.get()));
    }

    template<class T>
    inline bool operator<(const weak_ptr<T>& a, const weak_ptr<T>& b) {
        return compare<T*>::less(a.get(), b.get());
    }
    template<class T>
    inline bool operator==(const weak_ptr<T>& a, const weak_ptr<T>& b) {
        return compare<T*>::equal(a.get(), b.get());
    }
    template<class T>
    inline bool operator!=(const weak_ptr<T>& a, const weak_ptr<T>& b) {
        return compare<T*>::nequal(a.get(), b.get());
    }



    template<class T>
    struct ptr_deleter {
        inline void operator()(T* p) {
            typedef i8 complete_type_check[sizeof(T) ? 1 : -1];
            (void)sizeof(complete_type_check);
            delete p;
        }
    };
    /**
     * Scoped unique pointer handle.
     */
    template<class T, class Deleter = ptr_deleter<T>>
    class scoped_ptr {
    public:
        inline constexpr scoped_ptr() noexcept = default;
        template<class U>
        explicit scoped_ptr(U* p) noexcept : ptr((T*)p)
        {}
        inline scoped_ptr& operator=(T* p) {
            reset(p);
            return *this;
        }
        inline constexpr scoped_ptr(std::nullptr_t) : scoped_ptr() {}
        template<class U>
        inline scoped_ptr(scoped_ptr<U>&& sp) : ptr((T*)sp.release()) {}
        template<class U>
        inline scoped_ptr& operator=(scoped_ptr<U>&& sp) {
            reset((T*)sp.release());
            return *this;
        }
        inline ~scoped_ptr() { reset(); }

        inline T* operator->() const {
            return ptr;
        }
        inline T& operator*() const {
            return *ptr;
        }

        inline T* get() const {
            return ptr;
        }
        inline void reset(T* p = (T*)nullptr) {
            Deleter()(ptr);
            ptr = p;
        }
        inline T* release() {
            T* p = ptr;
            ptr = nullptr;
            return p;
        }
        inline operator bool() const {
            return ptr != nullptr;
        }
        inline bool is_null() const {
            return !ptr;
        }
    private:
        scoped_ptr(const scoped_ptr&);
        scoped_ptr& operator=(const scoped_ptr&);
        friend void swap(scoped_ptr<T>& a, scoped_ptr<T>& b);

        T* ptr = nullptr;
    };

    template<class T, class...Args>
    inline scoped_ptr<T> make_scoped(Args&&...args) {
        return scoped_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<class T>
    inline void swap(scoped_ptr<T>& a, scoped_ptr<T>& b) {
        swap(a.ptr, b.ptr);
    }
    template<class T>
    inline bool operator<(const scoped_ptr<T>& a, const scoped_ptr<T>& b) {
        return compare<T*>::less(a.get(), b.get());
    }
    template<class T>
    inline bool operator==(const scoped_ptr<T>& a, const scoped_ptr<T>& b) {
        return compare<T*>::equal(a.get(), b.get());
    }
    template<class T>
    inline bool operator!=(const scoped_ptr<T>& a, const scoped_ptr<T>& b) {
        return compare<T*>::nequal(a.get(), b.get());
    }
}

#endif //WHITEGEAR_SMART_PTR_HPP
