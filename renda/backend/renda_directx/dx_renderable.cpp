
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "dx_renderable.hpp"
#include "dx_bindable_index_buffer.hpp"
#include "scene/components/transform.hpp"

#if WG_WINDOWS

namespace wg {
    void dx_renderable::render(dx_graphics &gfx) noexcept {
        for (uint i = 0; i < mBinds.size(); ++i) {
            mBinds[i]->bind(gfx);
        }
        for (uint i = 0; i < mStaticBinds.size(); ++i) {
            mStaticBinds[i]->bind(gfx);
        }
        gfx.draw_indices(mIndexBuffer->get_count());
    }

    void dx_renderable::add_bind(unique_ptr<dx_bindable> bind) noexcept {
        mBinds.emplace_back(std::move(bind));
    }

    void dx_renderable::add_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept {
        assert(!mIndexBuffer && "Attempting to add index buffer a second time");
        mIndexBuffer = index_buffer.get();
        mBinds.emplace_back(std::move(index_buffer));
    }

    u64 dx_renderable::get_num_indices() const {
        return u64(mIndexBuffer->get_count());
    }

    void dx_renderable::add_static_bind(unique_ptr<dx_bindable> bind) noexcept {
        mStaticBinds.emplace_back(std::move(bind));
    }

    void dx_renderable::add_static_index_buffer(unique_ptr<dx_bindable_index_buffer> index_buffer) noexcept {
        assert(!mIndexBuffer && "Attempting to add index buffer a second time");
        mIndexBuffer = index_buffer.get();
        mStaticBinds.emplace_back(std::move(index_buffer));
    }

    void dx_renderable::set_index_from_static() {
        for (uint i = 0; i < mStaticBinds.size(); ++i) {
            if (const auto p = dynamic_cast<dx_bindable_index_buffer*>(mStaticBinds[i].get())) {
                mIndexBuffer = p;
                return;
            }
        }
    }
}

#endif
