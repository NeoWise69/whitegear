
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_EDITOR_APPLICATION_HPP
#define WHITEGEAR_EDITOR_APPLICATION_HPP

#include <runtime/runtime_application.hpp>

namespace wg {
    class editor_application : public runtime_application {
    public:
        inline editor_application() = default;
        inline ~editor_application() = default;

        int pre_init() override;
        int init() override;
    };
}

#endif //WHITEGEAR_EDITOR_APPLICATION_HPP
