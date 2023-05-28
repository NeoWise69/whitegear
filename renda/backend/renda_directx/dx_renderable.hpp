
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

        void render(dx_graphics& gfx) noexcept(!WG_BUILD_DEBUG);
        void add_bind(unique_ptr<dx_bindable> bind) noexcept(!WG_BUILD_DEBUG);
        void add_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept;
        material_data_t get_material_data() const;
    private:
        const dx_bindable_index_buffer* mIndexBuffer = nullptr;
        bounded_array<unique_ptr<dx_bindable>, 16> mBinds = {};
        entity_t mOwner = -1;
        const world_registry* pWorldRegistry = nullptr;
    };
}

#endif

#endif //WHITEGEAR_DX_RENDERABLE_HPP
