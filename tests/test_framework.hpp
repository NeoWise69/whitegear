
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_TEST_FRAMEWORK_HPP
#define WHITEGEAR_TEST_FRAMEWORK_HPP

#include <cstdlib>
#include <iostream>
#include <functional>
#include <chrono>
#include <sstream>

namespace test {
    using pass_function_t = std::function<bool()>;

    class timer {
    public:
        static auto now();
    };

    void start(const char* moduleName);
    void end(std::chrono::duration<float, std::milli> testTime);

    void pass(const pass_function_t& fn, const char* fnName, bool expectedError = false);
}

#define TEST(module_name, ...) { test::start(module_name); const auto _start_time_ = test::timer::now(); { __VA_ARGS__ } const auto _test_time_ = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(test::timer::now() - _start_time_); test::end(_test_time_); }
#define TEST_PASS(fnName) test::pass(fnName, #fnName);
#define TEST_PASS_ERR(fnName) test::pass(fnName, #fnName, true);

// IMPLEMENTATION

namespace test {

    namespace details {
        inline std::string get_time_string(std::chrono::duration<float, std::milli> dur) {
            auto d = dur.count();
            const char* pf = "ms";
            if (d > 1200.f) {
                d /= 1000.0f;
                pf = "s";
            }
            else if (d < 0.1f) {
                return { "" };
            }
            return std::to_string(d) + pf;
        }

        inline void ok() {
            fprintf(stdout, "\x1b[32mOk!\x1b[39m");
        }
        inline void err() {
            fprintf(stderr, "\x1b[31mErr!\x1b[39m");
        }
    }

    inline auto timer::now() {
        return std::chrono::system_clock::now();
    }

    inline void start(const char* moduleName) {
        fprintf(stdout, "\x1b[39m");
        std::cout << "Started tests of \'" << moduleName << "\' module..." << std::endl;
    }

    inline void end(std::chrono::duration<float, std::milli> testTime) {
        const auto timeStr = details::get_time_string(testTime);
        std::cout << "All tests clear! (" << timeStr << " total)" << std::endl;
    }

    inline void pass(const pass_function_t& fn, const char* fnName, bool expectedError) {
        fprintf(stdout, "\t\'%s()\'...", fnName);
        const auto startTime = timer::now();
        const bool result = fn();
        const auto endTime = timer::now();
        const auto executionTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(endTime - startTime);

        if (result) {
            if (expectedError) {
                details::err();
            }
            else {
                details::ok();
            }
        }
        else {
            if (expectedError) {
                details::ok();
            }
            else {
                details::err();
            }
        }

        const auto executionTimeString = details::get_time_string(executionTime);
        if (executionTimeString.size() > 1) {
            fprintf(stdout, " (took=%s)", executionTimeString.c_str());
        }
        else {
            fprintf(stdout, " (instant)");
        }

        std::cout << std::endl;
    }
}

#endif //WHITEGEAR_TEST_FRAMEWORK_HPP
