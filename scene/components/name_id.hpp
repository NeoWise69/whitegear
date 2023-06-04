
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_NAME_ID_HPP
#define WHITEGEAR_NAME_ID_HPP

#include <scene/component.hpp>
#include <core/containers/string.hpp>

namespace wg {
    struct component_name_id {
        WG_DECL_COMPONENT()

        string name;
    };
}

#endif //WHITEGEAR_NAME_ID_HPP
