
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_BINDABLE_PIXEL_SHADER_HPP
#define WHITEGEAR_DX_BINDABLE_PIXEL_SHADER_HPP

#include "dx_bindable.hpp"

#if WG_WINDOWS

namespace wg {
    class dx_bindable_pixel_shader : public dx_bindable {
    public:
        dx_bindable_pixel_shader(dx_graphics& gfx, const string& filename);
        void bind(dx_graphics& gfx) noexcept override;
    private:
        wrl::ComPtr<ID3D11PixelShader> mPixelShader = nullptr;
    };
}

#endif

#endif //WHITEGEAR_DX_BINDABLE_PIXEL_SHADER_HPP
