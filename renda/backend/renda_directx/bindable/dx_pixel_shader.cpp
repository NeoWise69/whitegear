
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_pixel_shader.hpp"

#if WG_WINDOWS

namespace wg {
    dx_bindable_pixel_shader::dx_bindable_pixel_shader(dx_graphics &gfx, const string &filename) {
        wrl::ComPtr<ID3DBlob> code = nullptr;
        WCHAR fname[MAX_PATH] = {};
        string::u8_to_u16(filename, fname, MAX_PATH);
        ret_t(D3DReadFileToBlob(fname, &code));
        gfx.create_pixel_shader(code, mPixelShader);
    }

    void dx_bindable_pixel_shader::bind(dx_graphics &gfx) const noexcept {
        gfx.ps()->bind(mPixelShader);
    }
}

#endif
