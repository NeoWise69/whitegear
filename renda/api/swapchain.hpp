
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_SWAPCHAIN_HPP
#define WHITEGEAR_SWAPCHAIN_HPP

#include <renda/api/common.hpp>

namespace wg {
    class window;
    namespace renda {
        class gpu_device;
        class target_buffer;

        class swapchain {
        public:
            struct create_info {
                const window *p_window;
                const display_info* p_display_info;
            };

            inline swapchain() noexcept = default;
            virtual ~swapchain() noexcept;

            bool create(const gpu_device* p_device, const create_info& ci) noexcept;
            void present() const noexcept;

            void get_target_buffer(const gpu_device &device, target_buffer &buffer) noexcept;
        private:
            i_object handle = nullptr;
        };
    }
}

#endif //WHITEGEAR_SWAPCHAIN_HPP
