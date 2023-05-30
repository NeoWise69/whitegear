
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_bindable_transform_constant_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    void dx_bindable_transform_constant_buffer::bind(dx_graphics &gfx) noexcept {

        material_data_t material_data = mParent.get_material_data();
        material_data.model_matrix = gfx.get_projection_matrix() * gfx.get_view_matrix() * material_data.model_matrix;

        mVCBMaterialData.update(gfx, material_data);
        mVCBMaterialData.bind(gfx);
    }
}

#endif
