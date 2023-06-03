
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_CONSTANT_BUFFER_BASE_HPP
#define WHITEGEAR_DX_CONSTANT_BUFFER_BASE_HPP

#include "dx_bindable_base.hpp"

#if WG_WINDOWS

namespace wg {
    template<class CB>
    class dx_bindable_constant_buffer_base : public dx_bindable_base {
    public:
        inline dx_bindable_constant_buffer_base(dx_graphics& gfx) {
            D3D11_BUFFER_DESC cbd;
            cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            cbd.Usage = D3D11_USAGE_DYNAMIC;
            cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            cbd.MiscFlags = 0u;
            cbd.ByteWidth = sizeof(CB);
            cbd.StructureByteStride = 0u;
            gfx.create_buffer(cbd, &mConstantBuffer);
        }
        inline dx_bindable_constant_buffer_base(dx_graphics& gfx, const CB& cb) {
            D3D11_BUFFER_DESC cbd;
            cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            cbd.Usage = D3D11_USAGE_DYNAMIC;
            cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            cbd.MiscFlags = 0u;
            cbd.ByteWidth = sizeof(cb);
            cbd.StructureByteStride = 0u;
            D3D11_SUBRESOURCE_DATA csd = {};
            csd.pSysMem = &cb;
            gfx.create_buffer(cbd, &mConstantBuffer, &csd);
        }
        inline void update(dx_graphics& gfx, const CB& cb) const {
            D3D11_MAPPED_SUBRESOURCE mr = {};
            gfx.map_resource(mConstantBuffer, D3D11_MAP_WRITE_DISCARD, &mr);
            memcpy(mr.pData, &cb, sizeof(cb));
            gfx.unmap_resource(mConstantBuffer);
        }
    protected:
        wrl::ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;
    };

    template<class CB>
    class dx_bindable_vertex_constant_buffer : public dx_bindable_constant_buffer_base<CB> {
        using dx_bindable_constant_buffer_base<CB>::mConstantBuffer;
    public:
        using dx_bindable_constant_buffer_base<CB>::dx_bindable_constant_buffer_base;

        inline void bind(dx_graphics& gfx) const noexcept override {
            gfx.vs()->set_constant_buffers((ID3D11Buffer**)mConstantBuffer.GetAddressOf(), 1);
        }
        inline void bind(dx_graphics& gfx, uint start_slot) const noexcept {
            gfx.vs()->set_constant_buffers((ID3D11Buffer**)mConstantBuffer.GetAddressOf(), 1, start_slot);
        }
    };

    template<class CB>
    class dx_bindable_pixel_constant_buffer : public dx_bindable_constant_buffer_base<CB> {
        using dx_bindable_constant_buffer_base<CB>::mConstantBuffer;
    public:
        using dx_bindable_constant_buffer_base<CB>::dx_bindable_constant_buffer_base;

        inline void bind(dx_graphics& gfx) const noexcept override {
            gfx.ps()->set_constant_buffers((ID3D11Buffer**)mConstantBuffer.GetAddressOf(), 1);
        }
        inline void bind(dx_graphics& gfx, uint start_slot) const noexcept {
            gfx.ps()->set_constant_buffers((ID3D11Buffer**)mConstantBuffer.GetAddressOf(), 1, start_slot);
        }
    };
}

#endif

#endif //WHITEGEAR_DX_CONSTANT_BUFFER_BASE_HPP
