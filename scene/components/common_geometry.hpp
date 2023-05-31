
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COMMON_GEOMETRY_HPP
#define WHITEGEAR_COMMON_GEOMETRY_HPP

#include <scene/component.hpp>

namespace wg {
    struct component_common_geometry {
        WG_DECL_COMPONENT()

        enum type_t : uint {
            COMMON_GEOMETRY_CUBE,
        };
        type_t type = COMMON_GEOMETRY_CUBE;
    };
}

#endif //WHITEGEAR_COMMON_GEOMETRY_HPP
