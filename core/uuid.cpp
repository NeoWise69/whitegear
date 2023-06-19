
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <core/required.hpp>
#include <core/utils.hpp>
#include <ctime>

namespace wg {
    namespace {
        random_engine rd(time(nullptr));
    }

    uuid::uuid() noexcept : card(generate_card()) {}
    const uuid uuid::invalid = uuid(false);

    constexpr uuid::cardholder uuid::generate_card() {
        cardholder card = {};

        constexpr u8 numset[] = { '0','1','2','3','4','5','6','7','8','9' };
        constexpr uint numset_size = sizeof(numset) / sizeof(numset[0]);

        for (u8 i = 1; i < max_length + 1; ++i) {
            if ((i % 5) == 0) {
                card.data[i - 1] = '-';
            }
            else {
                card.data[i - 1] = u8(numset[rd() % numset_size]);
            }
        }

        return card;
    }

    constexpr uuid::uuid(bool) noexcept {}
}
