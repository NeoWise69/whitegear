
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_INDEX_BUFFER_HPP
#define WHITEGEAR_DX_INDEX_BUFFER_HPP

#include "dx_bindable_base.hpp"
#include "math/geometry_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    class dx_bindable_index_buffer : public dx_bindable_base {
    public:
        template<uint VertexType>
        inline dx_bindable_index_buffer(dx_graphics& gfx, const geometry_buffer<VertexType>* p_buffer) : mCount(p_buffer->get_num_indices()) {
            D3D11_BUFFER_DESC ibd = {};
            ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
            ibd.Usage = D3D11_USAGE_DEFAULT;
            ibd.CPUAccessFlags = 0u;
            ibd.MiscFlags = 0u;
            ibd.ByteWidth = uint(mCount * sizeof(uint));
            ibd.StructureByteStride = sizeof(uint);
            D3D11_SUBRESOURCE_DATA isd = {};
            isd.pSysMem = p_buffer->get_indices();
            gfx.create_buffer(ibd, &mIndexBuffer, &isd);
        }
        void bind(dx_graphics& gfx) const noexcept override;
        inline uint get_count() const noexcept { return mCount; }
    private:
        wrl::ComPtr<ID3D11Buffer> mIndexBuffer = nullptr;
        uint mCount = {};
    };
}

#endif

#endif //WHITEGEAR_DX_INDEX_BUFFER_HPP
