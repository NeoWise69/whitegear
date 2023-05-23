
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_ENTITY_HPP
#define WHITEGEAR_ENTITY_HPP

#include <core/typedefs.hpp>

namespace wg {
    /**
     * Entity is a simple index, pointing towards data
     * inside storage.
     */
    typedef i64 entity_t;
    /**
     * Maximum amount of entities on the flight.
     */
    inline constexpr entity_t MAX_ENTITIES = 0x8000;
}

#endif //WHITEGEAR_ENTITY_HPP
