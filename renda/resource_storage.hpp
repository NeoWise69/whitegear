
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_RESOURCE_STORAGE_HPP
#define WHITEGEAR_RESOURCE_STORAGE_HPP

#include <core/required.hpp>
#include <core/containers/hashmap.hpp>
#include <core/containers/string_view.hpp>
#include <renda/api/gpu_resource.hpp>

namespace wg::renda {
    class resource_storage {
    public:
        inline resource_storage() noexcept = default;
        virtual ~resource_storage() noexcept = default;

        ref_ptr<gpu_resource>& operator[](const string_view& path);
        const ref_ptr<gpu_resource>& operator[](const string_view& path) const;
        bool exists(const string_view& path) const;

        static resource_storage& global();
    private:
        hashmap<string_view, ref_ptr<gpu_resource>> storage = {};
    };
}

#endif //WHITEGEAR_RESOURCE_STORAGE_HPP
