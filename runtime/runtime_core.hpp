
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RUNTIME_CORE_HPP
#define WHITEGEAR_RUNTIME_CORE_HPP

#include <runtime/runtime_module.hpp>
#include <core/containers/bounded_array.hpp>
#include <math/scalar_base.hpp>

namespace wg {
    struct runtime_tick_info {
        scalar delta_time;
    };

    class runtime_core {
    public:
        int initialize();
        int exit();

        int tick(runtime_tick_info* info);

        template<class T, class...Args>
        inline void add_module(Args&&...args) {
            mModules[T::module_id] = new T(this, std::forward<Args>(args)...);
        }

        template<class T, std::enable_if_t<std::is_base_of_v<runtime_module, T>, i32> = 0>
        inline T* get_module_by_id(const uint m_id) {
            return (T*)mModules[m_id];
        }

        inline bool is_running() const { return mIsRunning; }
    private:
        hashmap<uint, runtime_module*> mModules = {};
        bool mIsRunning;
    };
}

#endif //WHITEGEAR_RUNTIME_CORE_HPP
