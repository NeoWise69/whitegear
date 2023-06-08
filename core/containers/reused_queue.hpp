
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_REUSED_QUEUE_HPP
#define WHITEGEAR_REUSED_QUEUE_HPP

#include <core/typedefs.hpp>

namespace wg {
    /**
     * Simple queue structure that
     * should be OK for reusable usage
     * scenario. For example use it
     * as lightweight container for
     * storing pointers to renderable
     * objects for every frame.
     */
    template<class T>
    class reused_queue {
    public:
        /**
         * Node contains pointer to existing object,
         * and pointer to the next node.
         */
        struct node {
            inline node() noexcept = default;
            inline ~node() noexcept = default;
            inline explicit node(T* p) noexcept : p_object(p)
            {}

            T* p_object = nullptr;
            node* p_next = nullptr;
        };
        /**
         * const_iterator gives us a way to work with every
         * single object added in a container.
         */
        class const_iterator {
        public:
            inline const_iterator() noexcept = default;
            inline explicit const_iterator(node* p) noexcept : ptr(p) {}
            /**
             * Arrow operator.
             */
            inline const T* operator->() const { return ptr->p_object; }
            /**
             * Star operator for de-referencing
             */
            inline const T& operator*() const { return *(ptr->p_object); }
            /**
             * Postfix inc operator for next element access.
             */
            inline const_iterator& operator++() noexcept {
                ptr = ptr->p_next;
                return *this;
            }
            /**
             * Prefix inc operator for next element access.
             */
            inline const_iterator operator++(int) noexcept {
                const_iterator it = *this;
                ptr = ptr->p_next;
                return it;
            }
            /**
             * Simple comparison
             */
            inline bool operator==(const const_iterator& it) const {
                return ptr == it.ptr;
            }
            inline bool operator!=(const const_iterator& it) const {
                return ptr != it.ptr;
            }
        private:
            node* ptr = nullptr;
        };
        /**
         * const_iterator gives us a way to work with every
         * single object added in a container.
         */
        class iterator {
        public:
            inline iterator() noexcept = default;
            inline explicit iterator(node* p) noexcept : ptr(p) {}
            /**
             * Arrow operator.
             */
            inline T* operator->() const { return ptr->p_object; }
            /**
             * Arrow operator.
             */
            inline T* operator->() { return ptr->p_object; }
            /**
             * Star operator for de-referencing
             */
            inline T& operator*() const { return *(ptr->p_object); }
            /**
             * Star operator for de-referencing
             */
            inline T& operator*() { return *(ptr->p_object); }
            /**
             * Postfix inc operator for next element access.
             */
            inline iterator& operator++() noexcept {
                ptr = ptr->p_next;
                return *this;
            }
            /**
             * Prefix inc operator for next element access.
             */
            inline iterator operator++(int) noexcept {
                iterator it = *this;
                ptr = ptr->p_next;
                return it;
            }
            /**
             * Simple comparison
             */
            inline bool operator==(const iterator& it) const {
                return ptr == it.ptr;
            }
            inline bool operator!=(const iterator& it) const {
                return ptr != it.ptr;
            }
        private:
            node* ptr = nullptr;
        };

        inline reused_queue() noexcept = default;
        inline ~reused_queue() noexcept = default;
        /**
         * Pushes object pointer into itself (to last place),
         * but also tries to reuse already allocated nodes,
         * for example to prevent instant allocation on
         * every frame after reuse_queue<T>::reset() which
         * is resets all object pointers without corrupting
         * node pointers.
         */
        inline void push(T* p_object) noexcept {
            if (!p_head) {
                /**
                 * New reused_queue, create brand-new head and tail.
                 */
                p_head = p_tail = new node(p_object);
            }
            /**
             * First call to reset(--ted) reused_queue object,
             * reuse space at the HEAD.
             */
            else if (p_head == p_tail && !p_head->p_object) {
                node*& p_node = p_tail;
                p_node->p_object = p_object;
            }
            else {
                /**
                 * Push newly allocated node, or use existing
                 * one if provided.
                 */
                node*& p_node = p_tail->p_next;
                if (!p_node)
                    p_node = new node(p_object);
                else
                    p_node->p_object = p_object;
                p_tail = p_tail->p_next;
            }
        }
        /**
         * Clears every node's object pointer,
         * but keeps nodes alive for future usage.
         */
        inline void reset() noexcept {
            node* p_node = p_head;
            while (p_node) {
                p_node->p_object = nullptr; // <-- HERE
                p_node = p_node->p_next;
            }
            p_tail = p_head;
        }
        /**
         * Clear reused_queue completely with every node
         * de-allocation. (not affects objects at pointers).
         */
        inline void clear() {
            node* p_node = p_head;
            while (p_head) {
                p_node = p_head->p_next;
                delete p_head;
                p_head = p_node;
            }
            p_head = p_tail = nullptr;
        }
        /**
         * Simple range functions.
         */
        inline iterator begin() const noexcept { return iterator(p_head); }
        inline iterator end() const noexcept { return iterator((p_tail && p_tail->p_object) ? p_tail->p_next : p_tail); }
        inline iterator begin() noexcept { return iterator(p_head); }
        inline iterator end() noexcept { return iterator((p_tail && p_tail->p_object) ? p_tail->p_next : p_tail); }

    private:
        node* p_head = nullptr;
        node* p_tail = nullptr;
    };
}

#endif //WHITEGEAR_REUSED_QUEUE_HPP
