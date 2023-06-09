
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COMMON_CUBE_RENDERABLE_HPP
#define WHITEGEAR_COMMON_CUBE_RENDERABLE_HPP

#include <renda/drawing/renderable.hpp>

namespace wg::renda {
    class common_cube_renderable : public renderable {
    public:
        inline common_cube_renderable() noexcept = default;
        inline ~common_cube_renderable() noexcept override = default;

        common_cube_renderable(const gpu_device& device, const string_view& vs, const string_view& ps) noexcept;
    };
}

#endif //WHITEGEAR_COMMON_CUBE_RENDERABLE_HPP
