
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_NOISE_HPP
#define WHITEGEAR_NOISE_HPP

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace wg {
    class noise {
    public:
        inline explicit noise(scalar frequency = 1.0f, scalar amplitude = 1.0f, scalar lacunarity = 2.0f, scalar persistence = 0.5f) :
                            mFrequency(frequency), mAmplitude(amplitude), mLacunarity(lacunarity), mPersistence(persistence) {}

        static scalar perlin1d(scalar x);
        static scalar perlin2d(scalar x, scalar y);
        static scalar perlin3d(scalar x, scalar y, scalar z);

        scalar fractal1d(size_t numOctaves, scalar x) const;
        scalar fractal2d(size_t numOctaves, scalar x, scalar y) const;
        scalar fractal3d(size_t numOctaves, scalar x, scalar y, scalar z) const;
    private:
        scalar mFrequency;
        scalar mAmplitude;
        scalar mLacunarity;
        scalar mPersistence;
    };
}

#endif //WHITEGEAR_NOISE_HPP
