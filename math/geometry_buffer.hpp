
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_GEOMETRY_BUFFER_HPP
#define WHITEGEAR_GEOMETRY_BUFFER_HPP

#include <math/vertex.hpp>
#include <core/smart_ptr.hpp>
#include <new>

namespace wg {
    template<uint VertexType>
    class geometry_buffer {
    public:
        typedef vertex_t<VertexType> vertex_type_t;

        inline geometry_buffer() = default;
        inline ~geometry_buffer() {
            if (cb) {
                --cb->mRefCount;
                if (cb->mRefCount < 1) {
                    delete[] cb->mVertices;
                    delete cb;
                    cb = nullptr;
                }
            }
        }
        inline geometry_buffer(uint numVertices) : cb(new control_block{ new vertex_type_t[numVertices]() }) {}
        inline geometry_buffer(uint numIndices, bool) : cb(new control_block{ .mIndices = new uint[numIndices]() }) {}

        inline geometry_buffer(const geometry_buffer& o) : cb(o.cb) { ++cb->mRefCount; }
        inline geometry_buffer(geometry_buffer&& o) noexcept : cb(o.cb) { ++cb->mRefCount; }

        template<class...Args>
        inline void emplace_vertex(Args&&...args) {
            if (cb) {
                new(&cb->mVertices[cb->mNumVertices++]) vertex_type_t{std::forward<Args>(args)...};
            }
        }

        inline void emplace_index(uint v) {
            if (cb && cb->mIndices) {
                cb->mIndices[cb->mNumIndices++] = v;
            }
        }

        inline auto get_indices() const {
            if (cb) {
                return cb->mIndices;
            }
            return nullptr;
        }

        inline auto get_num_indices() const {
            if (cb) {
                return cb->mNumIndices;
            }
            return 0;
        }

        inline auto get_vertex(uint at) const {
            if (cb) {
                return cb->mVertices[at];
            }
            return vertex_type_t{};
        }

        inline auto get_vertices(uint* p_num_vertices = nullptr) const {
            if (cb) {
                if (p_num_vertices)
                    *p_num_vertices = cb->mNumVertices;
                return cb->mVertices;
            }
            return nullptr;
        }

        inline uint size() const { return cb ? cb->mNumVertices : 0; }

    private:
        struct control_block {
            vertex_type_t *mVertices = nullptr;
            uint mNumVertices = {};

            uint* mIndices = nullptr;
            uint mNumIndices = {};

            uint mRefCount = 0;
        } *cb;
    };
}

#endif //WHITEGEAR_GEOMETRY_BUFFER_HPP
