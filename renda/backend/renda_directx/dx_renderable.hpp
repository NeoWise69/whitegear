
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
    class dx_bindable;
    class dx_bindable_index_buffer;

    class dx_renderable {
    public:
        inline dx_renderable() = default;
        inline dx_renderable(const dx_renderable&) = delete;
        inline virtual ~dx_renderable() = default;

        inline dx_renderable(world_registry* p_world_reg, entity_t entt) : mOwner(entt), pWorldRegistry(p_world_reg)
        {}

        void render(dx_graphics& gfx) noexcept;
        void add_bind(unique_ptr<dx_bindable> bind) noexcept;
        static void add_static_bind(unique_ptr<dx_bindable> bind) noexcept;
        void add_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept;
        void add_static_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept;
        material_data_t get_material_data() const;
        inline u64 get_num_vertices() const { return mNumVertices; }
        u64 get_num_indices() const;
        inline auto get_bounding(const vec3& pos) const { mBoundingCube.set_position(pos); return mBoundingCube; }
        void set_index_from_static();
    private:
        const dx_bindable_index_buffer* mIndexBuffer = nullptr;
        bounded_array<unique_ptr<dx_bindable>, 16> mBinds = {};
        inline static bounded_array<unique_ptr<dx_bindable>, 16> mStaticBinds = {};
        entity_t mOwner = -1;
        const world_registry* pWorldRegistry = nullptr;

    protected:
        u64 mNumVertices = {};
        inline static geometry::cube mBoundingCube = {};
    };
}

#endif

#endif //WHITEGEAR_DX_RENDERABLE_HPP
