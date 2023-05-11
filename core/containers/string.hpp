
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_STRING_HPP
#define WHITEGEAR_STRING_HPP

#include <core/typedefs.hpp>

namespace wg {
    class string_impl;

    class string {
    public:
        virtual ~string();
        string();

        string(const string&);
        string(string&&) noexcept;
        string& operator=(const string&);
        string& operator=(string&&) noexcept;

        // access/write operators
        const char& operator[](i64 i) const;
        char& operator[](i64 i);
        // !access/write operators

    private:
        string clone() const;

        explicit string(string_impl*);

        string_impl* mImpl;
    };
}

#endif //WHITEGEAR_STRING_HPP
