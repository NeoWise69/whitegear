
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_INPUT_LAYOUT_HPP
#define WHITEGEAR_DX_INPUT_LAYOUT_HPP

#include "dx_bindable_base.hpp"

#if WG_WINDOWS

namespace wg {
    class dx_bindable_input_layout : public dx_bindable_base {
    public:
        dx_bindable_input_layout(dx_graphics& gfx, const bounded_array<D3D11_INPUT_ELEMENT_DESC, 16>& layout, ID3DBlob* p_bytecode);
        void bind(dx_graphics& gfx) const noexcept override;
    private:
        wrl::ComPtr<ID3D11InputLayout> mInputLayout = nullptr;
    };
}

#endif

#endif //WHITEGEAR_DX_INPUT_LAYOUT_HPP
