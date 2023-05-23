
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COMPONENT_HPP
#define WHITEGEAR_COMPONENT_HPP

#include <core/typedefs.hpp>
#include <limits.h>

/**
 * Macro used for component declaration,
 * setups it with COMPONENT_ID variable,
 * which is used to identify components.
 */
#define WG_DECL_COMPONENT() \
    inline static const component_id COMPONENT_ID = get_available_id();

namespace wg {
    /**
     * Component type is a simple index value pointing
     * towards data storage.
     */
    typedef u8 component_type_t;
    /**
     * Type for component identifying.
     */
    typedef u64 component_id;
    /**
     * Maximum amount of components on the flight.
     */
    inline constexpr component_type_t MAX_COMPONENTS = 0x80;
    /**
     * Returns new component id on each call.
     */
    component_id get_available_id();
    /**
     * Each component type has a unique ID (starting from 0),
     * which is used to represent a bit in the footprint.
     */
    class footprint {
    public:
        inline static constexpr i32 INT_BITS = CHAR_BIT * sizeof(i32);

        inline constexpr footprint() : mFp() {}
        inline ~footprint() = default;

        inline footprint(const footprint&) = default;
        inline footprint& operator=(const footprint&) = default;
        inline footprint(footprint&&) noexcept = default;
        inline footprint& operator=(footprint&&) noexcept = default;

        void set(i32 k);
        void set(i32 k, bool val);
        void reset(i32 k);
        void reset();
        i32 test(i32 k) const;
        void flip(i32 k);

        footprint& operator&=(const footprint& o);

        i32 operator[](i32 i) const;
    private:
        i32 mFp[MAX_COMPONENTS];
    };

    footprint operator&(const footprint& a, const footprint& b);

    bool operator==(const footprint& a, const footprint& b);
    bool operator!=(const footprint& a, const footprint& b);
}

#endif //WHITEGEAR_COMPONENT_HPP
