
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_RENDER_TARGET_BUFFER_HPP
#define WHITEGEAR_DX_RENDER_TARGET_BUFFER_HPP

#include "minimal.hpp"

#if WG_WINDOWS

namespace wg {
    class dx_render_target_buffer {
    public:
        inline dx_render_target_buffer() = default;
        inline ~dx_render_target_buffer() = default;
        dx_render_target_buffer(ID3D11Device* const p_device, uint width, uint height);

        inline auto get_texture() const { return mRenderTargetTexture; }
        inline auto get_view() const { return mRenderTargetView; }
        inline auto get_shader_resource_view() const { return mShaderResourceView; }
    private:
        wrl::ComPtr<ID3D11Texture2D> mRenderTargetTexture = nullptr;
        wrl::ComPtr<ID3D11RenderTargetView> mRenderTargetView = nullptr;
        wrl::ComPtr<ID3D11ShaderResourceView> mShaderResourceView = nullptr;
    };
}

#endif

#endif //WHITEGEAR_DX_RENDER_TARGET_BUFFER_HPP
