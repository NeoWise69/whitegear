
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
        inline geometry_buffer(uint num_vertices, uint num_indices) {
            cb = new control_block{
                new vertex_type_t[num_vertices]{},
                0,
                new uint[num_indices]{},
                0,
                1
            };
        }

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
            return (uint*)nullptr;
        }

        inline auto get_num_indices() const {
            if (cb) {
                return cb->mNumIndices;
            }
            return 0u;
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
            return (vertex_type_t*)nullptr;
        }

        inline uint get_num_vertices() const { return cb ? cb->mNumVertices : 0u; }

        inline static const geometry_buffer<VertexType>& get_cube() { return {}; }

    private:
        struct control_block {
            vertex_type_t *mVertices = nullptr;
            uint mNumVertices = {};

            uint* mIndices = nullptr;
            uint mNumIndices = {};

            uint mRefCount = 0;
        } *cb;
    };

    template<>
    inline const geometry_buffer<VERTEX_TYPE_MESH>& geometry_buffer<VERTEX_TYPE_MESH>::get_cube() {
        static bool mIsInitialized = false;
        static geometry_buffer<VERTEX_TYPE_MESH> cube_buffer(8, 36);
        if (!mIsInitialized) {
            cube_buffer.emplace_vertex(vec4(-1.0f,-1.0f,-1.0f, 1.0f), color32(255, 000, 255, 255));
            cube_buffer.emplace_vertex(vec4(1.0f,-1.0f,-1.0f, 1.0f), color32(255, 000, 000, 255));
            cube_buffer.emplace_vertex(vec4(-1.0f,1.0f,-1.0f, 1.0f), color32(000, 255, 000, 255));
            cube_buffer.emplace_vertex(vec4(1.0f,1.0f,-1.0f, 1.0f), color32(000, 000, 255, 255));
            cube_buffer.emplace_vertex(vec4(-1.0f,-1.0f,1.0f, 1.0f), color32(255, 255, 000, 255));
            cube_buffer.emplace_vertex(vec4(1.0f,-1.0f,1.0f, 1.0f), color32(000, 255, 255, 255));
            cube_buffer.emplace_vertex(vec4(-1.0f,1.0f,1.0f, 1.0f), color32(255, 255, 255, 255));
            cube_buffer.emplace_vertex(vec4(1.0f,1.0f,1.0f, 1.0f), color32(000, 000, 000, 255));

            cube_buffer.emplace_index(0); cube_buffer.emplace_index(2); cube_buffer.emplace_index(1);
            cube_buffer.emplace_index(2); cube_buffer.emplace_index(3); cube_buffer.emplace_index(1);
            cube_buffer.emplace_index(1); cube_buffer.emplace_index(3); cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(3); cube_buffer.emplace_index(7); cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(2); cube_buffer.emplace_index(6); cube_buffer.emplace_index(3);
            cube_buffer.emplace_index(3); cube_buffer.emplace_index(6); cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(4); cube_buffer.emplace_index(5); cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(4); cube_buffer.emplace_index(7); cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(0); cube_buffer.emplace_index(4); cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(2); cube_buffer.emplace_index(4); cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(0); cube_buffer.emplace_index(1); cube_buffer.emplace_index(4);
            cube_buffer.emplace_index(1); cube_buffer.emplace_index(5); cube_buffer.emplace_index(4);
            mIsInitialized = true;
        }

        return cube_buffer;
    }

    template<>
    inline const geometry_buffer<VERTEX_TYPE_NONE>& geometry_buffer<VERTEX_TYPE_NONE>::get_cube() {
        static bool mIsInitialized = false;
        static geometry_buffer<VERTEX_TYPE_NONE> cube_buffer(8, 36);
        if (!mIsInitialized) {
            cube_buffer.emplace_vertex(vec4(-1.0f,-1.0f,-1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(1.0f,-1.0f,-1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(-1.0f,1.0f,-1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(1.0f,1.0f,-1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(-1.0f,-1.0f,1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(1.0f,-1.0f,1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(-1.0f,1.0f,1.0f, 1.0f));
            cube_buffer.emplace_vertex(vec4(1.0f,1.0f,1.0f, 1.0f));

            cube_buffer.emplace_index(0); cube_buffer.emplace_index(2); cube_buffer.emplace_index(1);
            cube_buffer.emplace_index(2); cube_buffer.emplace_index(3); cube_buffer.emplace_index(1);
            cube_buffer.emplace_index(1); cube_buffer.emplace_index(3); cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(3); cube_buffer.emplace_index(7); cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(2); cube_buffer.emplace_index(6); cube_buffer.emplace_index(3);
            cube_buffer.emplace_index(3); cube_buffer.emplace_index(6); cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(4); cube_buffer.emplace_index(5); cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(4); cube_buffer.emplace_index(7); cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(0); cube_buffer.emplace_index(4); cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(2); cube_buffer.emplace_index(4); cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(0); cube_buffer.emplace_index(1); cube_buffer.emplace_index(4);
            cube_buffer.emplace_index(1); cube_buffer.emplace_index(5); cube_buffer.emplace_index(4);
            mIsInitialized = true;
        }

        return cube_buffer;
    }
}

#endif //WHITEGEAR_GEOMETRY_BUFFER_HPP
