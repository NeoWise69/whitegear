
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DIRECTX_MINIMAL_HPP
#define WHITEGEAR_DIRECTX_MINIMAL_HPP

#include <renda/rendering_engine.hpp>

#if WG_WINDOWS

/**
 * Include DirectX headers
 */
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <functional>
#include <DXErr.h>

namespace wrl = Microsoft::WRL;

namespace wg {
    template<>
    inline ret_t<HRESULT>::~ret_t() noexcept {
        if (!mReceived && FAILED(mValue)) {
            DXTRACE_ERR_MSGBOX("D3DCall Failed!", mValue);
        }
    }

    template<class TD3DResource>
    inline void SafeD3DRelease(TD3DResource& r) {
        if (r) {
            r->Release();
            r = nullptr;
        }
    }

    template<>
    inline bool ret_t<HRESULT>::is_ok() const noexcept {
        return !FAILED(mValue);
    }

    template<>
    inline string ret_t<HRESULT>::get_error_name() const noexcept {
        return DXGetErrorString(mValue);
    }

    template<>
    inline string ret_t<HRESULT>::get_error_desc() const noexcept {
        TCHAR buf[256];
        DXGetErrorDescription(mValue, buf, 256);
        return buf;
    }
}

#endif

#endif //WHITEGEAR_MINIMAL_HPP
