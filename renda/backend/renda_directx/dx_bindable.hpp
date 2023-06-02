
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_BINDABLE_HPP
#define WHITEGEAR_DX_BINDABLE_HPP

/**
 * DX_BINDABLE is an every graphics object that
 * is required to be bound before draw call.
 */

#include "dx_graphics.hpp"

#if WG_WINDOWS

namespace wg {
    /**
     * Simple base class for every 'bindable' directX resource.
     */
    class dx_bindable {
    public:
        virtual ~dx_bindable() = default;
        /**
         * Direct call to D3D for binding.
         */
        virtual void bind(dx_graphics& gfx) const noexcept = 0;
    };
}

#endif

#endif //WHITEGEAR_DX_BINDABLE_HPP
