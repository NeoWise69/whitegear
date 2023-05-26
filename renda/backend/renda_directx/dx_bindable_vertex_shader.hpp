
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_BINDABLE_VERTEX_SHADER_HPP
#define WHITEGEAR_DX_BINDABLE_VERTEX_SHADER_HPP

#include "dx_bindable.hpp"

#if WG_WINDOWS

namespace wg {
    class dx_bindable_vertex_shader : public dx_bindable {
    public:
        dx_bindable_vertex_shader(dx_graphics& gfx, const string& filename);
        void bind(dx_graphics& gfx) noexcept override;
        inline ID3DBlob* get_bytecode() const noexcept { return mBytecode.Get(); }
    private:
        wrl::ComPtr<ID3DBlob> mBytecode = nullptr;
        wrl::ComPtr<ID3D11VertexShader> mVertexShader = nullptr;
    };
}

#endif

#endif //WHITEGEAR_DX_BINDABLE_VERTEX_SHADER_HPP
