
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_HASHSET_HPP
#define WHITEGEAR_HASHSET_HPP

#include "hash_base.hpp"

#include <initializer_list>

namespace wg {
    template<class Key>
    class hashset : public hash_base {
    public:
        struct node : hash_node_base {
            inline node() noexcept = default;
            inline node(const Key& k) noexcept : key(k)
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

            Key key;
        };
        struct iterator : hash_iterator_base {
            inline iterator() noexcept = default;
            inline iterator(node* p) noexcept : hash_iterator_base(p)
            {}
            inline iterator& operator ++() noexcept {
                next_node();
                return *this;
            }
            inline iterator operator ++(int) noexcept {
                iterator it = *this;
                next_node();
                return it;
            }
            inline iterator& operator --() noexcept {
                prev_node();
                return *this;
            }
            inline iterator operator --(int) noexcept {
                iterator it = *this;
                prev_node();
                return it;
            }
            inline Key* operator->() const noexcept {
                return &((node*)mPtr)->key;
            }
            inline Key& operator*() const noexcept {
                return ((node*)mPtr)->key;
            }
        };
        struct const_iterator : hash_iterator_base {
            inline const_iterator() noexcept = default;
            inline const_iterator(node* p) noexcept : hash_iterator_base(p)
            {}
            inline const_iterator(const const_iterator& it) noexcept : hash_iterator_base(it.mPtr)
            {}
            inline const_iterator& operator=(const const_iterator& it) noexcept {
                mPtr = it.mPtr;
                return *this;
            }
            inline const_iterator& operator ++() noexcept {
                next_node();
                return *this;
            }
            inline const_iterator operator ++(int) noexcept {
                const_iterator it = *this;
                next_node();
                return it;
            }
            inline const_iterator& operator --() noexcept {
                prev_node();
                return *this;
            }
            inline const_iterator operator --(int) noexcept {
                const_iterator it = *this;
                prev_node();
                return it;
            }
            inline Key* operator->() const noexcept {
                return &((node*)mPtr)->key;
            }
            inline Key& operator*() const noexcept {
                return ((node*)mPtr)->key;
            }
        };

        inline hashset() noexcept {
            mAllocator = allocator_create(uint(sizeof(node)));
            mHead = mTail = _alloc_node();
        }
        inline hashset(const hashset& hs) noexcept {
            mAllocator = allocator_create(uint(sizeof(node)), hs.size() + 1);
            mHead = mTail = _alloc_node();
            *this = hs;
        }
        inline hashset(const std::initializer_list<Key>& list) noexcept {
            for (const auto& e : list) {
                insert(*e);
            }
        }
        inline ~hashset() noexcept {
            clear();
            _free_node(_tail());
            allocator_destroy(mAllocator);
            delete[] mPtrs;
        }
        inline hashset& operator=(const hashset& hs) noexcept {
            if (&hs != this) {
                clear();
                insert(hs);
            }
            return *this;
        }
        inline hashset& operator+=(const Key& key) noexcept {
            insert(key);
            return *this;
        }
        inline hashset& operator+=(const hashset& hs) noexcept {
            insert(hs);
            return *this;
        }

        inline iterator insert(const Key& key) noexcept {
            if (!mPtrs) {
                _allocate_buckets(size(), MIN_BUCKETS);
                _rehash();
            }
            const auto key_hash = _make_hash(key);
            node* p_existing = _find_node(key, key_hash);
            if (p_existing)
                return iterator(p_existing);
            node* p_new_node = _insert_node(_tail(), key);
            p_new_node->mDown = _get_ptrs()[key_hash];
            _get_ptrs()[key_hash] = p_new_node;
            if (size() > get_num_buckets() * MAX_LOAD_FACTOR) {
                _allocate_buckets(size(), get_num_buckets() << 1);
                _rehash();
            }
            return iterator(p_new_node);
        }
        inline iterator insert(const Key& key, bool& is_exists) noexcept {
            const auto old_size = size();
            iterator it = insert(key);
            is_exists = (size() == old_size);
            return it;
        }
        inline void insert(const hashset& hs) noexcept {
            const_iterator it = hs.begin();
            const_iterator e = hs.end();
            while (it != e)
                insert(*it++);
        }
        inline iterator insert(const const_iterator& it) noexcept {
            return iterator(insert(*it));
        }
        inline bool erase(const Key& key) noexcept {
            if (mPtrs) {

                const auto key_hash = _make_hash(key);
                node* prev = nullptr;
                auto* p_node = _find_node(key, key_hash, prev);
                if (!p_node) {
                    return false;
                }
                if (prev) {
                    prev->mDown = p_node->down();
                }
                else {
                    _get_ptrs()[key_hash] = p_node->down();
                }
                _erase_node(p_node);
                return true;
            }
            return false;
        }
        inline iterator erase(const iterator& it) noexcept {
            if (mPtrs && it.mPtr) {
                node* p_node = (node*)(it.mPtr);
                node* p_next = p_node->next();

                const auto key_hash = _make_hash(p_node->key);

                node* previous = nullptr;
                node* current = (node*)(_get_ptrs()[key_hash]);
                while (current && current != p_node) {
                    previous = current;
                    current = current->down();
                }

                assert(current == p_node);

                if (previous)
                    previous->mDown = p_node->down();
                else
                    _get_ptrs()[key_hash] = p_node->down();

                _erase_node(p_node);
                return iterator(p_next);
            }
            return end();
        }
        inline void clear() noexcept {
            _reset_ptrs();
            if (size()) {
                for (iterator it = begin(); it != end(); ++it) {
                    _free_node((node*)(it++.mPtr));
                    it.mPtr->mPrev = nullptr;
                }
                mHead = mTail;
                _set_size(0);
            }
        }

        inline const_iterator find(const Key& key) const noexcept {
            if (mPtrs) {
                const auto key_hash = _make_hash(key);
                node* p_node = _find_node(key, key_hash);
                if (p_node)
                    return const_iterator(p_node);
            }
            return end();
        }
        inline iterator find(const Key& key) noexcept {
            if (mPtrs) {
                const auto key_hash = _make_hash(key);
                node* p_node = _find_node(key, key_hash);
                if (p_node)
                    return iterator(p_node);
            }
            return end();
        }
        inline bool contains(const Key& key) const noexcept {
            if (mPtrs) {
                const auto key_hash = _make_hash(key);
                return _find_node(key, key_hash) != nullptr;
            }
            return false;
        }

        inline auto begin() noexcept { return iterator(_head()); }
        inline auto begin() const noexcept { return const_iterator(_head()); }
        inline auto end() noexcept { return iterator(_tail()); }
        inline auto end() const noexcept { return const_iterator(_tail()); }
        inline const Key& front() const noexcept { return *begin(); }
        inline const Key& back() const noexcept { return *(--end()); }
        using hash_base::size;
    private:
        inline node* _head() const noexcept {
            return (node*)(mHead);
        }
        inline node* _tail() const noexcept {
            return (node*)(mTail);
        }
        inline node* _alloc_node() noexcept {
            auto* p_new_node = (node*)(allocator_alloc(mAllocator));
            new(p_new_node) node();
            return p_new_node;
        }
        inline node* _alloc_node(const Key& key) noexcept {
            auto* p_new_node = (node*)(allocator_alloc(mAllocator));
            new(p_new_node) node(key);
            return p_new_node;
        }
        inline void _free_node(node* p_node) noexcept {
            (p_node)->~node();
            allocator_free(mAllocator, p_node);
        }
        inline void _rehash() noexcept {
            for (iterator it = begin(); it != end(); ++it) {
                auto* p_node = (node*)(it.mPtr);
                const auto key_hash = _make_hash(*it);
                p_node->mDown = _get_ptrs()[key_hash];
                _get_ptrs()[key_hash] = p_node;
            }
        }
        inline node* _find_node(const Key& key, u64 key_hash) const noexcept {
            auto* p_node = (node*)(_get_ptrs()[key_hash]);
            while (p_node) {
                if (p_node->key == key) {
                    return p_node;
                }
                p_node = p_node->down();
            }
            return nullptr;
        }
        inline node* _find_node(const Key& key, u64 key_hash, node*& prev) const noexcept {
            prev = nullptr;
            auto* p_node = (node*)(_get_ptrs()[key_hash]);
            while (p_node) {
                if (p_node->key == key) {
                    return p_node;
                }
                prev = p_node;
                p_node = p_node->down();
            }
            return nullptr;
        }
        inline node* _insert_node(node* dst, const Key& key) noexcept {
            if (dst) {
                node* p_new_node = _alloc_node(key);
                node* prev = dst->prev();
                p_new_node->mNext = dst;
                p_new_node->mPrev = prev;
                if (prev)
                    prev->mNext = p_new_node;
                dst->mPrev = p_new_node;
                if (dst == _head())
                    mHead = p_new_node;
                _set_size(size() + 1);
                return p_new_node;
            }
            return nullptr;
        }
        inline node* _erase_node(node* p_node) noexcept {
            if (!p_node || p_node == _tail())
                return _tail();

            node* prev = p_node->prev();
            node* next = p_node->next();
            if (prev)
                prev->mNext = next;
            next->mPrev = prev;
            if (p_node == _head())
                mHead = next;
            _free_node(p_node);
            _set_size(size() - 1);
            return next;
        }
        inline u64 _make_hash(const Key& key) const noexcept {
            return make_hash(key) & (get_num_buckets() - 1);
        }
    };
    template<class K>
    inline bool operator==(const hashset<K>& a, const hashset<K>& b) noexcept {

    }
    template<class K>
    inline bool operator!=(const hashset<K>& a, const hashset<K>& b) noexcept {

    }
}

#endif //WHITEGEAR_HASHSET_HPP
