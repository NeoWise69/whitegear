
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include "viewport.hpp"
#include <core/utils.hpp>

namespace wg {
    namespace {
        constexpr auto reference_aspect_value_16_9  = scalar(1920.0 / 1080.0);
        constexpr auto reference_aspect_value_16_10 = scalar(1920.0 / 1200.0);
        constexpr auto reference_aspect_value_4_3   = scalar(1600.0 / 1200.0);
        constexpr auto reference_aspect_value_21_9  = scalar(2560.0 / 1080.0);
        constexpr auto reference_aspect_value_32_9  = scalar(3840.0 / 1080.0);
        constexpr auto reference_aspect_value_1_1   = scalar(1920.0 / 1920.0);

        uint _get_reference_width(const scalar aspect) {
            if (aspect == reference_aspect_value_16_9 ||
                aspect == reference_aspect_value_16_10 ||
                aspect == reference_aspect_value_1_1)
                return 1920u;
            else if (aspect == reference_aspect_value_4_3)
                return 1600u;
            else if (aspect == reference_aspect_value_21_9)
                return 2560u;
            else if (aspect == reference_aspect_value_32_9)
                return 3840u;
            else
                return 800;
        }

        uint _get_reference_height(const scalar aspect) {
            if (aspect == reference_aspect_value_21_9 ||
                aspect == reference_aspect_value_32_9 ||
                aspect == reference_aspect_value_16_9)
                return 1080u;
            else if (aspect == reference_aspect_value_16_10
                    || aspect == reference_aspect_value_4_3)
                return 1200u;
            else if (aspect == reference_aspect_value_1_1)
                return 1920u;
            else
                return 600;
        }
    }

    aspect_ratio::aspect_ratio(aspect_ratio::standard f) {
        switch (f) {
            case f16_9: { mValue = reference_aspect_value_16_9; } break;
            case f16_10:{ mValue = reference_aspect_value_16_10; } break;
            case f4_3:  { mValue = reference_aspect_value_4_3; } break;
            case f21_9: { mValue = reference_aspect_value_21_9; } break;
            case f32_9: { mValue = reference_aspect_value_32_9; } break;
            case f1_1:  { mValue = reference_aspect_value_1_1; } break;
        }
    }

    uint aspect_ratio::get_reference_width() const {
        return _get_reference_width(mValue);
    }

    uint aspect_ratio::get_reference_height() const {
        return _get_reference_height(mValue);
    }

    void viewport::set_standard_aspect_ratio(aspect_ratio::standard ar) {
        mAspectRatio = aspect_ratio(ar);
        const auto min_size = min(mWidth, mHeight);
        const scalar f_aspect = mAspectRatio;
        mWidth = uint(scalar(min_size) * f_aspect);
        mHeight = min_size;
        mDirty = true;
    }

    void viewport::update() {
        if (mDirty) {
            mAspectRatio = aspect_ratio(mWidth, mHeight);
            mProjectionMatrix = perspective(mFieldOfView, mAspectRatio, mNearClipPlane, mFarClipPlane);
            mDirty = false;
            mIsResized = false;
        }
    }
}
