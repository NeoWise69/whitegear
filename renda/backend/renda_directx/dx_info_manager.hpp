
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_DX_INFO_MANAGER_HPP
#define WHITEGEAR_DX_INFO_MANAGER_HPP

#include "minimal.hpp"

#if WG_WINDOWS
struct IDXGIInfoQueue;

namespace wg {
    class dx_info_manager {
    public:
        dx_info_manager();
        ~dx_info_manager();

        inline dx_info_manager(const dx_info_manager&) = delete;
        inline dx_info_manager& operator=(const dx_info_manager&) = delete;
        inline dx_info_manager(dx_info_manager&&) noexcept = delete;
        inline dx_info_manager& operator=(dx_info_manager&&) noexcept = delete;

        void set() noexcept;
        void get_messages(bounded_array<string, 16>& msgs) const;

    private:
        u64 mNext = {};
        IDXGIInfoQueue* mIDXGIInfoQueue = {};
    };
}

#endif //WG_WINDOWS

#endif //WHITEGEAR_DX_INFO_MANAGER_HPP
