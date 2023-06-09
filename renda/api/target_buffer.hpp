
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_TARGET_BUFFER_HPP
#define WHITEGEAR_TARGET_BUFFER_HPP

#include <renda/api/common.hpp>
#include <math/viewport.hpp>
#include <math/vec4.hpp>

namespace wg::renda {
    class gpu_device;

    class target_buffer {
    public:
        inline target_buffer() noexcept = default;
        virtual ~target_buffer() noexcept;

        bool create(const gpu_device& device, const viewport* p_viewport, bool depth = true) noexcept;

        void clear(const gpu_device& device, const vec4& color = vec4(0, 0, 0, 1)) const noexcept;
        void bind(const gpu_device& device) const noexcept;

        inline i_object get_target_view() const noexcept {
            return target_view;
        }
        inline i_object get_depth_view() const noexcept {
            return depth_view;
        }
    private:
        friend class swapchain;
        i_object target_view = nullptr;
        i_object depth_view = nullptr;
    };
}

#endif //WHITEGEAR_TARGET_BUFFER_HPP
