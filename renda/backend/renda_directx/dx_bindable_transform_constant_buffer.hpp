
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_BINDABLE_TRANSFORM_CONSTANT_BUFFER_HPP
#define WHITEGEAR_DX_BINDABLE_TRANSFORM_CONSTANT_BUFFER_HPP

#include "dx_bindable_constant_buffer_base.hpp"
#include "dx_renderable.hpp"
#include <math/geometry.hpp>

#if WG_WINDOWS

namespace wg {
    class dx_bindable_transform_constant_buffer : public dx_bindable {
    public:
        inline dx_bindable_transform_constant_buffer(dx_graphics& gfx, const dx_renderable& parent)
            : mVCBMaterialData(gfx), mParent(parent)
        {}
        void bind(dx_graphics& gfx) noexcept override;
    private:
        dx_bindable_vertex_constant_buffer<material_data_t> mVCBMaterialData;
        const dx_renderable& mParent;
    };
}

#endif

#endif //WHITEGEAR_DX_BINDABLE_TRANSFORM_CONSTANT_BUFFER_HPP