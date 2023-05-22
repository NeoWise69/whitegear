
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RENDERER_API_HPP
#define WHITEGEAR_RENDERER_API_HPP

#include <core/typedefs.hpp>

namespace wg {
    /**
     * Since I'm trying to adapt WhiteGear Engine
     * at both windows and osx, there are will be
     * a good approach to build vulkan renderer
     * for UNIX, but WINDOWS will have a native
     * DirectX renderer backend.
     */
    class renderer_api {
    public:
        enum type : u32 {
            vulkan_api,
            directx
        };

        inline static type get_type() noexcept {
            return mType;
        }

    private:
        static type mType;
    };
}

#endif //WHITEGEAR_RENDERER_API_HPP
