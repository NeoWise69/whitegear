
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_REF_COUNTED_HPP
#define WHITEGEAR_REF_COUNTED_HPP

#include <core/typedefs.hpp>

namespace wg {
    struct ref_count {
        inline ~ref_count() noexcept {
            refs =
            weak_refs = -1;
        }

        i32 refs = {};
        i32 weak_refs = {};
    };

    class ref_counted {
    public:
        ref_counted() noexcept;
        virtual ~ref_counted() noexcept;

        void inc_ref() noexcept;
        void dec_ref() noexcept;
        inline i32 get_num_refs() const noexcept { return rc->refs; }
        inline i32 get_num_weaks() const noexcept { return rc->weak_refs - 1; }
        inline ref_count* get_ref_count_ptr() noexcept { return rc; }

    private:
        ref_counted(const ref_counted&);
        ref_counted& operator=(const ref_counted&);

        ref_count* rc = nullptr;
    };
}

#endif //WHITEGEAR_REF_COUNTED_HPP
