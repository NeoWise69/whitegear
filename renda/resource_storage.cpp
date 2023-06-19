
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <renda/resource_storage.hpp>
#include <core/image.hpp>

namespace wg::renda {
    resource_storage& resource_storage::global() {
        static resource_storage instance = {};
        return instance;
    }

    ref_ptr<gpu_resource> &resource_storage::operator[](const string_view &path) {
        return storage[path];
    }

    const ref_ptr<gpu_resource> &resource_storage::operator[](const string_view &path) const {
        return storage.at(path);
    }

    bool resource_storage::exists(const string_view &path) const {
        return storage.contains(path);
    }

}
