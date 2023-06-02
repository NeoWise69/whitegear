
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_bindable_per_frame_constant_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    void dx_bindable_per_frame_constant_buffer::bind(wg::dx_graphics &gfx) const noexcept {
        frame_data_t frame_data = {};
        frame_data.projection_matrix = gfx.get_projection_matrix();
        frame_data.view_matrix = gfx.get_view_matrix();

        mVCBFrameData.update(gfx, frame_data);
        mVCBFrameData.bind(gfx, 1);
    }
}

#endif