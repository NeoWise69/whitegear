
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
        inline static const auto MAX_MODULES = 32;

        int initialize();
        int exit();

        int tick(runtime_tick_info* info);

        template<class T, class...Args>
        void add_module(Args&&...args) {
            mModules.emplace_back(new T(this, std::forward<Args>(args)...));
        }

        inline bool is_running() const { return mIsRunning; }
    private:
        bounded_array<runtime_module*, MAX_MODULES> mModules;
        bool mIsRunning;
    };
}

#endif //WHITEGEAR_RUNTIME_CORE_HPP
