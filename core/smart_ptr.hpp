
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_SMART_PTR_HPP
#define WHITEGEAR_SMART_PTR_HPP

#include <core/typedefs.hpp>

#include <memory>

namespace wg {
    using std::shared_ptr;
    using std::make_shared;

    using std::unique_ptr;
    using std::make_unique;

    using std::static_pointer_cast;
    using std::dynamic_pointer_cast;
}

#endif //WHITEGEAR_SMART_PTR_HPP
