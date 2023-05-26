
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_renderable.hpp"
#include "dx_bindable_index_buffer.hpp"

#if WG_WINDOWS

namespace wg {
    void dx_renderable::render(dx_graphics &gfx) noexcept(!WG_BUILD_DEBUG) {
        for (uint i = 0; i < mBinds.size(); ++i) {
            mBinds[i]->bind(gfx);
        }
        gfx.draw_indices(mIndexBuffer->get_count());
    }

    void dx_renderable::add_bind(unique_ptr<dx_bindable> bind) noexcept(!WG_BUILD_DEBUG) {
        mBinds.emplace_back(std::move(bind));
    }

    void dx_renderable::add_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept {
        assert(!mIndexBuffer && "Attempting to add index buffer a second time");
        mIndexBuffer = index_buffer.get();
        mBinds.emplace_back(std::move(index_buffer));
    }
}

#endif
