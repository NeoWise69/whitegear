
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERABLE_HPP
#define WHITEGEAR_RENDERABLE_HPP

#include <renda/api/gpu_resource.hpp>
#include <scene/entity.hpp>
#include <math/geometry.hpp>
#include <core/smart_ptr.hpp>

namespace wg::renda {
    class renderable : public ref_counted {
    public:
        inline renderable() = default;
        inline renderable(const renderable&) = delete;
        inline virtual ~renderable() = default;

        void render(gpu_device& device) noexcept;
        void add_bind(ref_ptr<gpu_resource> bind) noexcept;
        static void add_static_bind(ref_ptr<gpu_resource> bind) noexcept;
        void add_index_buffer(ref_ptr<geometry_buffer> index_buffer) noexcept;
        void add_static_index_buffer(ref_ptr<geometry_buffer> index_buffer) noexcept;
        inline u64 get_num_vertices() const { return num_vertices; }
        u64 get_num_indices() const;
        inline auto get_bounding(const vec3& pos) const { bounding_box.set_position(pos); return bounding_box; }
        inline auto& get_bounding(const vec3& pos) { bounding_box.set_position(pos); return bounding_box; }
        void set_index_from_static();
        inline auto get_transform_matrix() const { return *p_transform_matrix; }
        inline void set_transform_matrix_ptr(const mat4* p_transform) { p_transform_matrix = p_transform; }
        inline bool is_transform_ptr_provided() const { return p_transform_matrix != nullptr; }

    private:
        const geometry_buffer* p_index_buffer = {};
        bounded_array<ref_ptr<gpu_resource>, 16> draw_resources = {};
        inline static bounded_array<ref_ptr<gpu_resource>, 16> static_draw_resources = {};
        const mat4* p_transform_matrix = nullptr;
    protected:
        u64 num_vertices = {};
        inline static geometry::box bounding_box = {};
    };
}

#endif //WHITEGEAR_RENDERABLE_HPP
