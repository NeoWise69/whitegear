
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/drawing/constant_buffer_per_frame.hpp>

namespace wg::renda {
    constant_buffer_per_frame::constant_buffer_per_frame(const gpu_device &device, const mat4 *p_proj, const mat4 *p_view) noexcept {
        resource_type = GPU_RESOURCE_CONSTANT_BUFFER;
        p_projection_matrix = p_proj;
        p_view_matrix = p_view;
        memory_data_t mem = {};
        mem.size = sizeof(frame_data_t);
        buffer = make_ref<constant_buffer>(device, mem);
    }
    void constant_buffer_per_frame::bind(gpu_device &device) const noexcept {
        frame_data_t frame_data = {};
        frame_data.projection_matrix = *p_projection_matrix;
        frame_data.view_matrix = *p_view_matrix;
        buffer->update(device, &frame_data);
        buffer->bind(device, 1u);
    }
}
