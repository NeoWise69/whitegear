
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_bindable_input_layout.hpp"

#if WG_WINDOWS

namespace wg {
    dx_bindable_input_layout::dx_bindable_input_layout(wg::dx_graphics &gfx,
                                                       const bounded_array<D3D11_INPUT_ELEMENT_DESC, 16> &layout,
                                                       ID3DBlob *p_bytecode) {
        gfx.create_input_layout(layout.data(), layout.size(), p_bytecode, mInputLayout);
    }
    void dx_bindable_input_layout::bind(dx_graphics &gfx) noexcept {
        gfx.ia()->set_input_layout(mInputLayout);
    }
}

#endif
