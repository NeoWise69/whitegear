
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "world.hpp"
#include "scene/components/transform.hpp"
#include <scene/components/name_id.hpp>

namespace wg {
    entity_t world::controls::create_entity(const char *name_id) {
        const entity_t e = pRegistry->entity_create();
        pRegistry->add_component(e, component_name_id{ name_id });
        pRegistry->add_component(e, component_transform{{}, {}, vec3(1)});
        entities->at(e) = true;
        return e;
    }

    void world::controls::destroy_entity(entity_t e) {
        pRegistry->entity_destroy(e);
        entities->erase(e);
    }
}
