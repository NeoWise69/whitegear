
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_info_manager.hpp"

#if WG_WINDOWS

#include <dxgidebug.h>

namespace wg {
    dx_info_manager::dx_info_manager() {
        typedef HRESULT(WINAPI *PFN_DXGIGetDebugInterface)(const IID&, void**);

        WG_NOT_IMPLEMENTED
    }

    dx_info_manager::~dx_info_manager() {
        WG_NOT_IMPLEMENTED

    }

    void dx_info_manager::set() noexcept {
        WG_NOT_IMPLEMENTED

    }

    void dx_info_manager::get_messages(bounded_array<wg::string, 16> &msgs) const {
        WG_NOT_IMPLEMENTED

    }
}

#endif
