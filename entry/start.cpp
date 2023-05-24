
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <editor/editor_application.hpp>

#if WG_WINDOWS
#include <windows.h>
#endif

int main() {
#if WG_WINDOWS
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    if (!wg::is_support(wg::HW_SSE)) {
        wg::out
        .panic("failed to execute wg_app, current machine CPU is not support SSE instructions.");
    }

#if WG_BUILD_EDITOR
    static wg::editor_application app;
#endif

    struct application_exit_guard {
        ~application_exit_guard() {
            app.request_exit();
        }
    } exit_guard = {};

    if (const auto code = app.pre_init()) {
        return code;
    }
    if (const auto code = app.init()) {
        return code;
    }
    if (const auto code = app.run()) {
        return code;
    }

    return 0;
}
