
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

template<class ComObject>
inline void D3DSafeRelease(ComObject& o) {
    if (o) {
        o->Release();
        o = nullptr;
    }
}

#define D3DCALL(fn) \
{ HRESULT hr = fn; \
    if (FAILED(hr)) { \
        TCHAR msg[1024]; \
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | \
        FORMAT_MESSAGE_ALLOCATE_BUFFER | \
        FORMAT_MESSAGE_IGNORE_INSERTS, \
        nullptr, hr, \
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), \
        (LPTSTR)msg, 0, nullptr); \
        out         \
        .error("D3DCALL has failed!: %s", msg); \
    }           \
}

namespace wrl = Microsoft::WRL;

#endif

#endif //WHITEGEAR_MINIMAL_HPP
