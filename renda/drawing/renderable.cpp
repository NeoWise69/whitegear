
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/drawing/renderable.hpp>

namespace wg::renda {
    void renderable::render(gpu_device& device) noexcept {
        for (uint i = 0; i < draw_resources.size(); ++i) {
            draw_resources[i]->bind(device);
        }
        for (uint i = 0; i < static_draw_resources.size(); ++i) {
            static_draw_resources[i]->bind(device);
        }
        device.draw_indices(p_index_buffer->get_count());
    }

    void renderable::add_bind(ref_ptr<gpu_resource> bind) noexcept {
        draw_resources.emplace_back(std::move(bind));
    }

    void renderable::add_index_buffer(ref_ptr<geometry_buffer> ib) noexcept {
        p_index_buffer = ib.get();
        draw_resources.emplace_back(std::move(ib));
    }

    u64 renderable::get_num_indices() const {
        return u64(p_index_buffer->get_count());
    }

    void renderable::add_static_bind(ref_ptr<gpu_resource> bind) noexcept {
        static_draw_resources.emplace_back(std::move(bind));
    }

    void renderable::add_static_index_buffer(ref_ptr<geometry_buffer> ib) noexcept {
        p_index_buffer = ib.get();
        static_draw_resources.emplace_back(std::move(ib));
    }

    void renderable::set_index_from_static() {
        for (uint i = 0; i < static_draw_resources.size(); ++i) {
            if (static_draw_resources[i]->get_resource_type() == GPU_RESOURCE_INDEX_BUFFER) {
                p_index_buffer = (geometry_buffer*)static_draw_resources[i].get();
                return;
            }
        }
    }
}
