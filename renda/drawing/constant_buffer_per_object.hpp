
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_CONSTANT_BUFFER_PER_OBJECT_HPP
#define WHITEGEAR_CONSTANT_BUFFER_PER_OBJECT_HPP

#include <renda/api/gpu_resource.hpp>
#include <renda/drawing/renderable.hpp>

namespace wg::renda {
    class constant_buffer_per_object : public gpu_resource {
    public:
        inline constant_buffer_per_object() noexcept = default;
        ~constant_buffer_per_object() noexcept override = default;

        constant_buffer_per_object(const gpu_device& device, const uint obj_size, const renderable* p_renderable) noexcept;

        void bind(gpu_device& device) const noexcept override;
    private:
        ref_ptr<constant_buffer> buffer = {};
        const renderable* p_renderable = nullptr;
    };
}

#endif //WHITEGEAR_CONSTANT_BUFFER_PER_OBJECT_HPP
