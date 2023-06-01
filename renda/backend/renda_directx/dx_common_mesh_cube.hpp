
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_COMMON_MESH_CUBE_HPP
#define WHITEGEAR_DX_COMMON_MESH_CUBE_HPP

#include "dx_scene_renderable.hpp"
#include <math/geometry_buffer.hpp>

#if WG_WINDOWS

namespace wg {
    class dx_common_mesh_cube : public dx_renderable {
    public:
        struct create_info {
            string_view filename_vs;
            string_view filename_ps;
        };

        explicit dx_common_mesh_cube(dx_graphics& gfx, const create_info& cv_create_info);
    };
}

#endif

#endif //WHITEGEAR_DX_COMMON_MESH_CUBE_HPP
