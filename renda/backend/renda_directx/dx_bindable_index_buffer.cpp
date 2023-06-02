
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_bindable_index_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    void dx_bindable_index_buffer::bind(dx_graphics &gfx) const noexcept {
        gfx.ia()->set_index_buffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT);
    }
}

#endif
