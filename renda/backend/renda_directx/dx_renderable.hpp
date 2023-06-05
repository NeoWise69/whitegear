
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_RENDERABLE_HPP
#define WHITEGEAR_DX_RENDERABLE_HPP

#include "dx_graphics.hpp"
#include <math/vertex.hpp>
#include <scene/entity.hpp>

#if WG_WINDOWS

namespace wg {
    class dx_bindable_base;
    class dx_bindable_index_buffer;

    class dx_renderable {
    public:
        inline dx_renderable() = default;
        inline dx_renderable(const dx_renderable&) = delete;
        inline virtual ~dx_renderable() = default;

        void render(dx_graphics& gfx) noexcept;
        void add_bind(unique_ptr<dx_bindable_base> bind) noexcept;
        static void add_static_bind(unique_ptr<dx_bindable_base> bind) noexcept;
        void add_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept;
        void add_static_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept;
        inline u64 get_num_vertices() const { return mNumVertices; }
        u64 get_num_indices() const;
        inline auto get_bounding(const vec3& pos) const { mBoundingCube.set_position(pos); return mBoundingCube; }
        inline auto& get_bounding(const vec3& pos) { mBoundingCube.set_position(pos); return mBoundingCube; }
        void set_index_from_static();
        inline auto get_transform_matrix() const { return *mTransformPtr; }
        inline void set_transform_matrix_ptr(const mat4* p_transform) { mTransformPtr = p_transform; }
        inline bool is_transform_ptr_provided() const { return mTransformPtr != nullptr; }
    private:
        const dx_bindable_index_buffer* mIndexBuffer = nullptr;
        bounded_array<unique_ptr<dx_bindable_base>, 16> mBinds = {};
        inline static bounded_array<unique_ptr<dx_bindable_base>, 16> mStaticBinds = {};
        const mat4* mTransformPtr = nullptr;

    protected:
        u64 mNumVertices = {};

        inline static geometry::box mBoundingCube = {};
    };
}

#endif

#endif //WHITEGEAR_DX_RENDERABLE_HPP
