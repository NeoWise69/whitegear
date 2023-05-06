
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/
#include "test_framework.hpp"

#include "core_arch_support.hpp"
#include "core_logger.hpp"
#include "containers_array_view.hpp"
#include "containers_string_view.hpp"
#include "math_vectors.hpp"

auto successful_test() -> bool {
    return true;
}
auto failed_test() -> bool {
    return false;
}

auto main(int argc, char** argv) -> int {
    TEST("core",
         TEST_PASS(successful_test)
         TEST_PASS_ERR(failed_test)
         TEST_PASS(core_arch_support_test)
         TEST_PASS(core_logger_test)
         TEST_PASS(containers_array_view_test)
         TEST_PASS(containers_string_view_test)
         TEST_PASS(math_vectors_test)
    );
}
