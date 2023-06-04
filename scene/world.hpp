
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_WORLD_HPP
#define WHITEGEAR_WORLD_HPP

#include <scene/world_registry.hpp>
#include <functional>

namespace wg {
    class rendering_engine;

    struct world_tick_data {
        real delta_time;
    };
    struct world_statistics {
        u64 draw_calls;
        u64 vertices_per_frame;
        u64 indices_per_frame;
        u64 vertices_on_scene;
        u64 indices_on_scene;
    };

    class world {
    public:
        class rendering_system : public scene_system {
        public:
            WG_DECL_SCENE_SYSTEM()

            inline rendering_system(world_registry* reg) : registry(reg) {}

            bool render_scene(rendering_engine* renda, world_tick_data &data);

        private:
            world_registry* registry = nullptr;
        };

        class common_mesh_rendering_system : public scene_system {
        public:
            WG_DECL_SCENE_SYSTEM()

            inline common_mesh_rendering_system(world_registry* reg) : registry(reg) {}

            bool render_common_meshes(rendering_engine* renda, world_tick_data &data);

        private:
            world_registry* registry = nullptr;
        };

        bool initialize(rendering_engine* p_renda);
        bool load();
        bool unload();
        bool uninitialize();

        bool on_tick(world_tick_data& data);

        inline world_statistics& stats() { return mStats; }
        inline const world_statistics& stats() const { return mStats; }

        inline void on_each_entity(const std::function<void(entity_t, world_registry*)>& fn) {
            for (uint i = 0; i < pEntities->size(); ++i)
                fn(pEntities->at(i), &registry);
        }

    private:
        world_statistics mStats = {};
        rendering_engine* renda = nullptr;
        world_registry registry = {};
        bounded_array<entity_t, MAX_ENTITIES>* pEntities = nullptr;

        shared_ptr<rendering_system> renderingSystem = nullptr;
        shared_ptr<common_mesh_rendering_system> commonMeshRenderingSystem = nullptr;
    };
}

#endif //WHITEGEAR_WORLD_HPP
