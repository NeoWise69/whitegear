
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_BINDABLE_GEOMETRY_TOPOLOGY_HPP
#define WHITEGEAR_DX_BINDABLE_GEOMETRY_TOPOLOGY_HPP

#include "dx_bindable.hpp"

#if WG_WINDOWS

namespace wg {
    class dx_bindable_geometry_topology : public dx_bindable {
    public:
        inline dx_bindable_geometry_topology(dx_graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY topo) : mTopo(topo) {}
        void bind(dx_graphics& gfx) const noexcept override;
    private:
        D3D11_PRIMITIVE_TOPOLOGY mTopo = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    };
}

#endif

#endif //WHITEGEAR_DX_BINDABLE_GEOMETRY_TOPOLOGY_HPP
