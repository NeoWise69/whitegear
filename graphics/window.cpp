
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/window.hpp>

#include <GLFW/glfw3.h>
#include <stdexcept>

bool GIsGLFWInitialized = false;

namespace wg::gfx {

    void platform_update() {
        glfwPollEvents();
    }

    window::window(gfx::window_create_info *p_info) {
        open(p_info);
    }

    window::~window() {
        glfwDestroyWindow(mWindow);
        if (GIsGLFWInitialized) {
            glfwTerminate();
            GIsGLFWInitialized = false;
        }
    }

    void window::open(window_create_info *p_info) {
        mInfo.x = p_info->x;
        mInfo.y = p_info->y;
        mInfo.w = p_info->w;
        mInfo.h = p_info->h;
        mInfo.title = p_info->title;

        {   /* first ever glfw instance creation */
            if (!GIsGLFWInitialized) {
                glfwInit();
                GIsGLFWInitialized = true;
            }
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        auto monitor = p_info->fullscreen ? glfwGetPrimaryMonitor() : nullptr;
        auto tmp = glfwCreateWindow(p_info->w, p_info->h, p_info->title.c_str(), monitor, nullptr);
        if (!tmp) {
            char err[1024]{};
            glfwGetError((const char**)&err);
            throw std::runtime_error(err);
        }
        glfwShowWindow(tmp);
        glfwSetWindowUserPointer(tmp, &mInfo);

        glfwSetWindowCloseCallback(tmp, [](GLFWwindow* window){
            auto* info = (window_info*)glfwGetWindowUserPointer(window);
            if (info) {
                info->alive = false;
            }
        });

        glfwSetWindowSizeCallback(tmp, [](GLFWwindow* window, int w, int h) {
            auto* info = (window_info*)glfwGetWindowUserPointer(window);
            if (info) {
                info->w = w;
                info->h = h;
            }
        });

        glfwSetWindowPosCallback(tmp, [](GLFWwindow* window, int x, int y) {
            auto* info = (window_info*)glfwGetWindowUserPointer(window);
            if (info) {
                info->x = x;
                info->y = y;
            }
        });

        mWindow = tmp;
        mInfo.alive = true;
    }
}
