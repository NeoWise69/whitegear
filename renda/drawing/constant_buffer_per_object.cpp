
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/drawing/constant_buffer_per_object.hpp>

namespace wg::renda {
    constant_buffer_per_object::constant_buffer_per_object(const gpu_device &device, const uint obj_size,
                                            const renderable *pr) noexcept {
        p_renderable = pr;
        memory_data_t memory_data = {};
        memory_data.size = obj_size;
        buffer = make_ref<constant_buffer>(device, memory_data);
    }

    void constant_buffer_per_object::bind(gpu_device &device) const noexcept {
        material_data_t material_data = {};
        material_data.model_matrix = p_renderable->get_transform_matrix();

        buffer->update(device, &material_data);
        buffer->bind(device);
    }
}
