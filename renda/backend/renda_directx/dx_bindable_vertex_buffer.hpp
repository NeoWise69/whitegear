
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_BINDABLE_VERTEX_BUFFER_HPP
#define WHITEGEAR_DX_BINDABLE_VERTEX_BUFFER_HPP

#include "dx_bindable.hpp"
#include <math/geometry_buffer.hpp>

#if WG_WINDOWS

namespace wg {
    class dx_bindable_vertex_buffer : public dx_bindable {
    public:
        inline ~dx_bindable_vertex_buffer() override = default;

        template<uint VertexType>
        inline dx_bindable_vertex_buffer(dx_graphics& gfx, const geometry_buffer<VertexType>* buffer) : mStride(sizeof(vertex_t<VertexType>)) {
            D3D11_BUFFER_DESC bd = {};
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.CPUAccessFlags = 0u;
            bd.MiscFlags = 0u;

            D3D11_SUBRESOURCE_DATA sd = {};
            uint num_vertices = {};
            sd.pSysMem = buffer->get_vertices(&num_vertices);

            bd.ByteWidth = uint(sizeof(vertex_t<VertexType>) * num_vertices);
            bd.StructureByteStride = sizeof(vertex_t<VertexType>);

            gfx.create_buffer(bd, &mVertexBuffer, &sd);
        }

        void bind(dx_graphics& gfx) noexcept override;
    private:
        uint mStride = {};
        wrl::ComPtr<ID3D11Buffer> mVertexBuffer = nullptr;
    };
}

#endif

#endif //WHITEGEAR_DX_BINDABLE_VERTEX_BUFFER_HPP
