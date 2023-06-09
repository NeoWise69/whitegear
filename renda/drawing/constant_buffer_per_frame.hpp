
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CONSTANT_BUFFER_PER_FRAME_HPP
#define WHITEGEAR_CONSTANT_BUFFER_PER_FRAME_HPP

#include <renda/api/gpu_resource.hpp>
#include <math/vertex.hpp>
#include <core/smart_ptr.hpp>

namespace wg::renda {
    class constant_buffer_per_frame : public gpu_resource {
    public:
        inline constant_buffer_per_frame() noexcept = default;
        ~constant_buffer_per_frame() noexcept override = default;

        constant_buffer_per_frame(const gpu_device& device, const mat4* p_proj, const mat4* p_view) noexcept;

        void bind(gpu_device& device) const noexcept override;
    private:
        ref_ptr<constant_buffer> buffer = {};
        const mat4* p_projection_matrix = nullptr;
        const mat4* p_view_matrix = nullptr;
    };
}

#endif //WHITEGEAR_CONSTANT_BUFFER_PER_FRAME_HPP
