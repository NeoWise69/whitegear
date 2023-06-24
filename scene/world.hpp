
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

        class entities_update_system : public scene_system {
        public:
            WG_DECL_SCENE_SYSTEM()

            inline entities_update_system(world_registry* reg) : registry(reg) {}

            bool update(world_tick_data &data);

        private:
            world_registry* registry = nullptr;
        };

        class controls {
        public:
            inline controls() = default;

            inline ~controls() = default;

            inline controls(world *p_world)
                    : pRegistry(&p_world->registry), entities(&p_world->entities) {}

            inline void on_each_entity(const std::function<void(entity_t, world_registry *)> &fn) {
                for (auto& [e, _] : *entities)
                    fn(e, pRegistry);
            }

            entity_t create_entity(const char *name_id);
            void destroy_entity(entity_t e);

            template<class T>
            inline bool has_component(entity_t e) const {
                return pRegistry->has_component<T>(e);
            }

            template<class T>
            inline T& get_component(entity_t e) {
                return pRegistry->get_component<T>(e);
            }

            template<class T>
            inline void remove_component(entity_t e) {
                pRegistry->remove_component<T>(e);
            }

            template<class T>
            inline void add_component(entity_t e) {
                pRegistry->add_component<T>(e, {});
            }

            template<class T>
            inline void add_component(entity_t e, T c) {
                pRegistry->add_component(e, c);
            }

            template<class T>
            inline const T& get_component(entity_t e) const {
                return pRegistry->get_component<T>(e);
            }

            inline bool is_ready() const {
                return pRegistry && entities;
            }

        private:
            world_registry *pRegistry = nullptr;
            hashmap<entity_t, bool> *entities = nullptr;
        };

        bool initialize(rendering_engine* p_renda);
        bool load();
        bool unload();
        bool uninitialize();

        bool on_tick(world_tick_data& data);

        inline world_statistics& stats() { return mStats; }
        inline const world_statistics& stats() const { return mStats; }

    private:
        world_statistics mStats = {};
        rendering_engine* renda = nullptr;
        world_registry registry = {};
        hashmap<entity_t, bool> entities = {};

        ref_ptr<rendering_system> renderingSystem = nullptr;
        ref_ptr<common_mesh_rendering_system> commonMeshRenderingSystem = nullptr;
        ref_ptr<entities_update_system> update_system = nullptr;
    };
}

#endif //WHITEGEAR_WORLD_HPP
