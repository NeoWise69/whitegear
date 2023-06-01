
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_SYSTEM_HPP
#define WHITEGEAR_SYSTEM_HPP

#include <scene/entity.hpp>
#include <scene/component.hpp>
#include <core/containers/set.hpp>
#include <core/smart_ptr.hpp>
#include <core/containers/hashmap.hpp>

/**
 * Macro used for system declaration,
 * setups it with SYSTEM_ID variable,
 * which is used to identify systems.
 */
#define WG_DECL_SCENE_SYSTEM() \
    inline static const scene_system_id SCENE_SYSTEM_ID = get_available_id();

namespace wg {
    class scene_system {
    public:
        set<entity_t> entities = {};
    };

    typedef u64 scene_system_id;

    class scene_system_manager {
    public:
        inline scene_system_manager() : mFootprints(), mSystems()
        {}
        inline ~scene_system_manager() = default;

        template<class T, class...Args>
        inline shared_ptr<T> register_system(Args&&...args) {
            assert(mSystems.find(T::SCENE_SYSTEM_ID) == mSystems.end() && "Registering system more than once!");

            auto s = make_shared<T>(std::forward<Args>(args)...);
            mSystems.insert(T::SCENE_SYSTEM_ID, s);
            return s;
        }

        template<class T>
        inline void assign_footprint(const footprint& f) {
            assert(mSystems.find(T::SCENE_SYSTEM_ID) != mSystems.end() && "System used before being registered!");

            mFootprints.insert(T::SCENE_SYSTEM_ID, f);
        }

        void on_entity_destroyed(entity_t entt);
        void on_entity_footprint_changed(entity_t entt, const footprint& f);

    private:
        hashmap<scene_system_id, footprint> mFootprints;
        hashmap<scene_system_id, shared_ptr<scene_system>> mSystems;
    };

}

#endif //WHITEGEAR_SYSTEM_HPP
