
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
    class geometry_buffer {
    public:
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
                new mesh_vertex[num_vertices]{},
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
                new(&cb->mVertices[cb->mNumVertices++]) mesh_vertex{std::forward<Args>(args)...};
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
            return mesh_vertex{};
        }

        inline auto get_vertices(uint* p_num_vertices = nullptr) const {
            if (cb) {
                if (p_num_vertices)
                    *p_num_vertices = cb->mNumVertices;
                return cb->mVertices;
            }
            return (mesh_vertex*)nullptr;
        }

        inline uint get_num_vertices() const { return cb ? cb->mNumVertices : 0u; }

        static const geometry_buffer& get_cube();

    private:
        struct control_block {
            mesh_vertex *mVertices = nullptr;
            uint mNumVertices = {};

            uint* mIndices = nullptr;
            uint mNumIndices = {};

            uint mRefCount = 0;
        } *cb;
    };

    inline const geometry_buffer& geometry_buffer::get_cube() {
        static bool mIsInitialized = false;
        static geometry_buffer cube_buffer(14, 36);
        if (!mIsInitialized) {
            constexpr auto side = real(1);
            random_engine re;

            cube_buffer.emplace_vertex(vec4(-side,-side,-side, 1.0f),   vec2(2.0f / 3.0f, 0.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 14
            cube_buffer.emplace_vertex(vec4(side,-side,-side, 1.0f),    vec2(1.0f / 3.0f, 0.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 13
            cube_buffer.emplace_vertex(vec4(-side,side,-side, 1.0f),    vec2(2.0f / 3.0f, 1.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 12
            cube_buffer.emplace_vertex(vec4(side,side,-side, 1.0f),     vec2(1.0f / 3.0f, 1.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 11
            cube_buffer.emplace_vertex(vec4(-side,-side,side, 1.0f),    vec2(2.0f / 3.0f, 3.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 10
            cube_buffer.emplace_vertex(vec4(side,-side,side, 1.0f),     vec2(1.0f / 3.0f, 3.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 09
            cube_buffer.emplace_vertex(vec4(-side,side,side, 1.0f),     vec2(2.0f / 3.0f, 2.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 08
            cube_buffer.emplace_vertex(vec4(side,side,side, 1.0f),      vec2(1.0f / 3.0f, 2.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 07
            cube_buffer.emplace_vertex(vec4(-side,-side,-side, 1.0f),   vec2(2.0f / 3.0f, 4.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 06
            cube_buffer.emplace_vertex(vec4(side,-side,-side, 1.0f),    vec2(1.0f / 3.0f, 4.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 05
            cube_buffer.emplace_vertex(vec4(-side,-side,-side, 1.0f),   vec2(3.0f / 3.0f, 1.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 04
            cube_buffer.emplace_vertex(vec4(-side,-side,side, 1.0f),    vec2(3.0f / 3.0f, 2.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 03
            cube_buffer.emplace_vertex(vec4(side,-side,-side, 1.0f),    vec2(0.0f / 3.0f, 1.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 02
            cube_buffer.emplace_vertex(vec4(side,-side,side, 1.0f),     vec2(0.0f / 3.0f, 2.0f / 4.0f), color32(u8(re(0xff)), u8(re(0xff)), u8(re(0xff)), 0xff), vec3(0), vec3(0), vec3(0)); // 01

            // THESE INDICES ARE NOT ORDERED! DO NOT EDIT!!!!!
            cube_buffer.emplace_index(13);
            cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(12);
            cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(3);
            cube_buffer.emplace_index(12);
            cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(11);
            cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(11);
            cube_buffer.emplace_index(10);
            cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(4);
            cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(4);
            cube_buffer.emplace_index(7);
            cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(3);
            cube_buffer.emplace_index(3);
            cube_buffer.emplace_index(6);
            cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(9);
            cube_buffer.emplace_index(8);
            cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(5);
            cube_buffer.emplace_index(8);
            cube_buffer.emplace_index(4);
            cube_buffer.emplace_index(1);
            cube_buffer.emplace_index(3);
            cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(1);
            cube_buffer.emplace_index(2);
            cube_buffer.emplace_index(0);

            mIsInitialized = true;
        }

        return cube_buffer;
    }

}

#endif //WHITEGEAR_GEOMETRY_BUFFER_HPP
