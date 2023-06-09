
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_EXPERIMENTAL_HASHMAP_HPP
#define WHITEGEAR_EXPERIMENTAL_HASHMAP_HPP

#include "hash_base.hpp"
#include <core/utils.hpp>

#include <initializer_list>

namespace wg {
    template<class K, class V>
    class hashmap : hash_base {
    public:
        typedef K key_type;
        typedef V value_type;

        struct key_value {
            inline key_value() noexcept
                : first(key_type())
            {}
            inline key_value(const key_type& key, const value_type& val) noexcept
                : first(key), second(val)
            {}
            inline key_value(const key_value& kv) noexcept
                : first(kv.first), second(kv.second)
            {}

            inline bool operator==(const key_value& kv) const noexcept {
                return first == kv.first && second == kv.second;
            }
            inline bool operator!=(const key_value& kv) const noexcept {
                return !(first == kv.first && second == kv.second);
            }

            const key_type first;
            value_type second;
        private:
            key_value& operator=(const key_value&);
        }; // !key_value

        struct node : hash_node_base {
            inline node() noexcept = default;
            inline node(const key_type& key, const value_type& val) noexcept
                : pair(key, val)
            {}

            inline auto next() const noexcept {
                return (node*)mNext;
            }
            inline auto prev() const noexcept {
                return (node*)mPrev;
            }
            inline auto down() const noexcept {
                return (node*)mDown;
            }

            key_value pair;
        }; // !node

        struct iterator : hash_iterator_base {
            inline iterator() noexcept = default;
            inline iterator(node* p) noexcept : hash_iterator_base(p) {}
            inline iterator& operator++() noexcept {
                next_node();
                return *this;
            }
            inline iterator& operator--() noexcept {
                prev_node();
                return *this;
            }
            inline iterator operator++(int) noexcept {
                iterator t = *this;
                next_node();
                return t;
            }
            inline iterator operator--(int) noexcept {
                iterator t = *this;
                prev_node();
                return t;
            }
            inline key_value* operator->() const noexcept {
                return &((node*)(mPtr))->pair;
            }
            inline key_value& operator*() const noexcept {
                return ((node*)(mPtr))->pair;
            }
        }; // !iterator

        struct const_iterator : hash_iterator_base {
            inline const_iterator() noexcept = default;
            inline const_iterator(node* p) noexcept : hash_iterator_base(p) {}
            inline const_iterator(const iterator& it) noexcept : hash_iterator_base(it.mPtr) {}
            inline const_iterator& operator=(const iterator& it) noexcept {
                mPtr = it.mPtr;
                return *this;
            }
            inline const_iterator& operator++() noexcept {
                next_node();
                return *this;
            }
            inline const_iterator& operator--() noexcept {
                prev_node();
                return *this;
            }
            inline const_iterator operator++(int) noexcept {
                const_iterator t = *this;
                next_node();
                return t;
            }
            inline const_iterator operator--(int) noexcept {
                const_iterator t = *this;
                prev_node();
                return t;
            }
            inline const key_value* operator->() const noexcept {
                return &((node*)(mPtr))->pair;
            }
            inline const key_value& operator*() const noexcept {
                return ((node*)(mPtr))->pair;
            }
        }; // !iterator

        typedef pair<key_type, value_type> pair_type;

        // definition down below
        inline hashmap() noexcept {
            mAllocator = allocator_create(sizeof(node));
            mHead = mTail = _allocate_node();
        }
        inline hashmap(const hashmap& map) noexcept {
            mAllocator = allocator_create(sizeof(node), map.size() + 1);
            mHead = mTail = _allocate_node();
            *this = map;
        }
        inline hashmap(const std::initializer_list<pair_type>& list) noexcept : hashmap() {
            for (auto it = list.begin(); it != list.end(); ++it) {
                insert(*it);
            }
        }
        inline ~hashmap() noexcept {
            clear();
            _free_node(_tail());
            allocator_destroy(mAllocator);
            delete[] mPtrs;
        }
        inline hashmap& operator=(const hashmap& map) noexcept {
            if (&map != this) {
                clear();
                insert(map);
            }
            return *this;
        }
        inline hashmap& operator+=(const pair_type& p) noexcept {
            insert(p);
            return *this;
        }
        inline hashmap& operator+=(const hashmap& map) noexcept {
            insert(map);
            return *this;
        }

        inline value_type& operator[](const key_type& key) noexcept {
            if (!mPtrs) {
                return _insert_node(key, value_type(), false)->pair.second;
            }
            const auto key_hash = _make_hash(key);
            auto* p_node = _find_node(key, key_hash);
            return p_node ? p_node->pair.second : _insert_node(key, value_type(), false)->pair.second;
        }

        inline const value_type& at(const key_type& key) const noexcept {
            const auto key_hash = _make_hash(key);
            auto* p_node = _find_node(key, key_hash);
            return p_node->pair.second;
        }

        inline value_type& at(const key_type& key) noexcept {
            if (!mPtrs) {
                return _insert_node(key, value_type(), false)->pair.second;
            }
            const auto key_hash = _make_hash(key);
            auto* p_node = _find_node(key, key_hash);
            return p_node ? p_node->pair.second : _insert_node(key, value_type(), false)->pair.second;
        }

        inline hashmap& populate(const key_type& key, const value_type& val) {
            operator[](key) = val;
            return *this;
        }
        template<class...Args>
        inline hashmap& populate(const key_type& key, const value_type& val, Args&&...args) {
            operator[](key) = val;
            return populate(args...);
        }

        inline iterator insert(const key_type& key, const value_type& v) noexcept {
            return iterator(_insert_node(key, v));
        }
        inline iterator insert(const pair_type& p) noexcept {
            return iterator(_insert_node(p.first, p.second));
        }
        inline iterator insert(const pair_type& p, bool& b_exists) noexcept {
            const auto old_size = size();
            iterator ret(_insert_node(p.first, p.second));
            b_exists = (size() == old_size);
            return ret;
        }
        inline void insert(const hashmap& map) noexcept {
            auto it = map.begin();
            auto _end = map.end();
            while (it != _end) {
                _insert_node(it->first, it->second);
                ++it;
            }
        }
        inline iterator insert(const const_iterator& it) noexcept {
            return iterator(_insert_node(it->first, it->second));
        }
        inline void insert(const const_iterator& f, const const_iterator& l) noexcept {
            auto it = f;
            while (it != l) {
                _insert_node(*it++);
            }
        }

        inline bool erase(const key_type& key) noexcept {
            if (!mPtrs) return false;
            const auto key_hash = _make_hash(key);
            node* p_prev = nullptr;
            auto* p_node = _find_node(key, key_hash, p_prev);
            if (!p_node) {
                return false;
            }
            if (p_prev) {
                p_prev->mDown = p_node->down();
            }
            else {
                _get_ptrs()[key_hash] = p_node->down();
            }
            _erase_node(p_node);
            return true;
        }

        inline iterator erase(const iterator& it) noexcept {
            if (mPtrs && it.mPtr) {
                auto* p_node = (node*)(it.mPtr);
                auto* p_next = p_node->next();
                const auto key_hash = _make_hash(p_node->pair.first);
                node* p_prev = nullptr;
                auto* current = (node*)(_get_ptrs()[key_hash]);
                if (current && current != p_node) {
                    p_prev = current;
                    current = current->down();
                }
                assert(current == p_node);
                if (p_prev) {
                    p_prev->mDown = p_node->down();
                }
                else {
                    _get_ptrs()[key_hash] = p_node->down();
                }
                _erase_node(p_node);
                return iterator(p_next);
            }
            else {
                return end();
            }
        }

        inline iterator begin() noexcept { return iterator(_head()); }
        inline const_iterator begin() const noexcept { return iterator(_head()); }
        inline iterator end() noexcept { return iterator(_tail()); }
        inline const_iterator end() const noexcept { return iterator(_tail()); }
        inline const key_value& front() const noexcept { return *begin(); }
        inline const key_value& back() const noexcept { return *end(); }
        using hash_base::size;

        inline iterator find(const key_type& key) noexcept {
            if (!mPtrs) return end();
            const auto key_hash = _make_hash(key);
            auto* p_node = _find_node(key, key_hash);
            if (p_node) {
                return iterator(p_node);
            }
            else {
                return end();
            }
        }
        inline const_iterator find(const key_type& key) const noexcept {
            if (!mPtrs) return end();
            const auto key_hash = _make_hash(key);
            auto* p_node = _find_node(key, key_hash);
            if (p_node) {
                return const_iterator(p_node);
            }
            else {
                return end();
            }
        }

        inline bool contains(const key_type& key) const noexcept {
            if (!mPtrs) return false;
            const auto key_hash = _make_hash(key);
            return _find_node(key, key_hash) != nullptr;
        }

        inline bool try_get(const key_type& key, value_type& v) const noexcept {
            if (!mPtrs) return false;
            const auto key_hash = _make_hash(key);
            auto* p_node = _find_node(key, key_hash);
            if (p_node) {
                v = p_node->pair.second;
                return true;
            }
            return false;
        }

        inline void clear() noexcept {
            _reset_ptrs();
            if (size()) {
                for (auto it = begin(); it != end();) {
                    _free_node((node*)(it++.mPtr));
                    it.mPtr->mPrev = nullptr;
                }
                mHead = mTail;
                _set_size(0u);
            }
        }
    private:
        inline node* _head() const noexcept { return (node*)mHead; }
        inline node* _tail() const noexcept { return (node*)mTail; }
        inline node* _find_node(const key_type& key, u64 key_hash) const noexcept {
            auto* n = (node*)(_get_ptrs()[key_hash]);
            while (n) {
                if (n->pair.first == key) return n;
                n = n->down();
            }
            return nullptr;
        }
        inline node* _find_node(const key_type& key, u64 key_hash, node*& p_prev) noexcept {
            p_prev = nullptr;
            auto* n = (node*)(_get_ptrs()[key_hash]);
            while (n) {
                if (n->pair.first == key) return n;
                p_prev = n;
                n = n->down();
            }
            return nullptr;
        }
        inline void _rehash() noexcept {
            for (auto it = begin(); it != end(); ++it) {
                auto* n = (node*)(it.mPtr);
                const auto key_hash = _make_hash(it->first);
                n->mDown = _get_ptrs()[key_hash];
                _get_ptrs()[key_hash] = n;
            }
        }
        inline void _free_node(node* p_node) noexcept {
            (p_node)->~node();
            allocator_free(mAllocator, p_node);
        }
        inline node* _allocate_node(const key_type& key, const value_type& val) noexcept {
            auto* p_node = (node*)(allocator_alloc(mAllocator));
            new(p_node) node(key, val);
            return p_node;
        }
        inline node* _allocate_node() noexcept {
            auto* p_node = (node*)(allocator_alloc(mAllocator));
            new(p_node) node();
            return p_node;
        }
        inline node* _erase_node(node* p_node) noexcept {
            if (p_node && p_node != mTail) {
                auto* prev = p_node->prev();
                auto* next = p_node->next();
                if (prev) {
                    prev->mNext = next;
                }
                next->mPrev = prev;
                if (p_node == _head()) {
                    mHead = next;
                }
                _free_node(p_node);
                _set_size(size() - 1);
                return next;
            }
            else {
                return _tail();
            }
        }
        inline node* _insert_node(node* dst, const key_type& key, const value_type& val) noexcept {
            if (!dst) return nullptr;

            auto* new_node = _allocate_node(key, val);
            auto* prev = dst->prev();
            new_node->mNext = dst;
            new_node->mPrev = prev;
            if (prev) {
                prev->mNext = new_node;
            }
            dst->mPrev = new_node;
            if (dst == _head()) {
                mHead = new_node;
            }
            _set_size(size() + 1);
            return new_node;
        }
        /**
         * Insert a key and the value, and return either the new or existing one.
         */
        inline node* _insert_node(const key_type& key, const value_type& val, bool b_find_existing = true) noexcept {
            if (!mPtrs) {
                _allocate_buckets(size(), MIN_BUCKETS);
                _rehash();
            }
            const auto key_hash = _make_hash(key);
            if (b_find_existing) {
                auto* ex = _find_node(key, key_hash);
                if (ex) {
                    ex->pair.second = val;
                    return ex;
                }
            }
            auto* new_node = _insert_node(_tail(), key, val);
            new_node->mDown = _get_ptrs()[key_hash];
            _get_ptrs()[key_hash] = new_node;
            if (size() > get_num_buckets() * MAX_LOAD_FACTOR) {
                _allocate_buckets(size(), get_num_buckets() << 1);
                _rehash();
            }
            return new_node;
        }

        inline u64 _make_hash(const key_type& key) const noexcept {
            return make_hash(key) & (get_num_buckets() - 1);
        }
    };

    template<class K, class V>
    inline bool operator==(const hashmap<K, V>& a, const hashmap<K, V>& b) noexcept {
        if (a.size() != b.size()) return false;
        auto it = a.begin();
        while (it != a.end()) {
            auto j = b.find(it->first);
            if (j == b.end() || j->second != it->second) {
                return false;
            }
            ++it;
        }
        return true;
    }

    template<class K, class V>
    inline bool operator!=(const hashmap<K, V>& a, const hashmap<K, V>& b) noexcept {
        return !(a == b);
    }

    template<class K, class V>
    inline typename hashmap<K, V>::const_iterator begin(const hashmap<K, V>& hm) noexcept {
        return hm.begin();
    }
    template<class K, class V>
    inline typename hashmap<K, V>::const_iterator end(const hashmap<K, V>& hm) noexcept {
        return hm.end();
    }
    template<class K, class V>
    inline typename hashmap<K, V>::iterator begin(hashmap<K, V>& hm) noexcept {
        return hm.begin();
    }
    template<class K, class V>
    inline typename hashmap<K, V>::iterator end(hashmap<K, V>& hm) noexcept {
        return hm.end();
    }

}

#endif //WHITEGEAR_HASHMAP_HPP
