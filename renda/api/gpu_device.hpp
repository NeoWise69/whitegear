
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_GPU_DEVICE_HPP
#define WHITEGEAR_GPU_DEVICE_HPP

#include <core/typedefs.hpp>
#include <core/containers/string.hpp>
#include <renda/api/common.hpp>

namespace wg {
    class window;
    class viewport;
    /**
     * GPUDevice is just a handle to low-level GPU
     * representation. Client code can't get access
     * to it's internal state.
     */
    namespace renda {
     class gpu_device {
     public:
         struct description {
             uint vram_mb = {};
             string desc_string = {};
         };

         inline gpu_device() noexcept = default;
         virtual ~gpu_device() noexcept;

         bool initialize(const window *p_window) noexcept;
         void update_viewport(const viewport& vp) const noexcept;

         void draw_vertices(uint count) const;
         void draw_indices(uint count) const;

         inline i_object get_device_instance() const noexcept { return device_instance; }
         inline i_object get_device_context() const noexcept { return device_context; }
         inline const display_info &get_screen_info() const noexcept { return s_info; }
         inline const description& get_description() const { return device_desc; }

     private:
         i_object device_instance = nullptr;
         i_object device_context = nullptr;
         description device_desc = {};
         display_info s_info = {};
     };
    }
}

#endif //WHITEGEAR_GPU_DEVICE_HPP
