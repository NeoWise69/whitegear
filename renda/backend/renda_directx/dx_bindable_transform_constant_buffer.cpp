
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_bindable_transform_constant_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    extern window* GWindow;

    void dx_bindable_transform_constant_buffer::bind(dx_graphics &gfx) noexcept {

        static const mat4 proj = perspective(radians(65.0f), GWindow->get_aspect(), 0.05f, 1000.0f);

        material_data_t material_data = mParent.get_material_data();
        material_data.model_matrix = proj * gfx.get_view_matrix() * material_data.model_matrix;

        mVCBMaterialData.update(gfx, material_data);
        mVCBMaterialData.bind(gfx);
    }
}

#endif
