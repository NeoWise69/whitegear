
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/api/gpu_resource.hpp>

#include "minimal.hpp"

namespace wg::renda {
    namespace {
        D3D_PRIMITIVE_TOPOLOGY _get_d3d11_topology(e_topology topo) {
            switch (topo) {
                case TOPOLOGY_LINE_LIST: return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                case TOPOLOGY_TRIANGLE_LIST: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                case TOPOLOGY_TRIANGLE_STRIP: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
                default:
                    return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
            }
        }
    }

    void topology::bind(gpu_device &device) const noexcept {
        auto context = (ID3D11DeviceContext*)(device.get_device_context());
        context->IASetPrimitiveTopology(_get_d3d11_topology(topo));
    }
}
