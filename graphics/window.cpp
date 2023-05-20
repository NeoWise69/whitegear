
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/window.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

bool GIsGLFWInitialized = false;

namespace wg {

    window::window(window_create_info *p_info) {
        open(p_info);
    }

    window::~window() {
        request_close();
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

        glfwSetKeyCallback(tmp, [](GLFWwindow* window, int _key, int scancode, int action, int mods) {
            auto* info = (window_info*)glfwGetWindowUserPointer(window);
            if (info) {
                /**
                 * btw window here is useless)
                 */
            }

            auto& kbd = input::get().get_keyboard();
            auto& kbd_state = kbd.get_state();
            switch (action) {
                case GLFW_REPEAT:
                case GLFW_PRESS: {
                    kbd_state.keys[_key] = keyboard_input::KEY_STATE_PRESSED;
                    break;
                }
                case GLFW_RELEASE: {
                    kbd_state.keys[_key] = keyboard_input::KEY_STATE_RELEASED;
                    kbd_state.released_keys.emplace_back(key(_key));
                    break;
                }
                default:
                    break;
            }
        });

        mWindow = tmp;
        mInfo.alive = true;

        out
        .trace("window[%s, %dx%d] has been created.", p_info->title.c_str(), p_info->w, p_info->h)
        ;
    }

    void window::platform_update() {
        auto& kbd = input::get().get_keyboard();
        auto& kbd_state = kbd.get_state();
        auto& released_keys = kbd_state.released_keys;
        for (u8 i = 0; i < released_keys.size(); ++i) {
            key& k = released_keys[i];
            kbd_state.keys[k] = keyboard_input::KEY_STATE_IDLE;
        }
        released_keys.clear();

        glfwPollEvents();
    }

    void window::request_close() {
        mInfo.alive = false;
        if (mWindow) {
            glfwDestroyWindow(mWindow);
            mWindow = nullptr;
        }
        if (GIsGLFWInitialized) {
            glfwTerminate();
            GIsGLFWInitialized = false;
        }
    }

/* void window::get_vk_surface(instance *instance, VkSurfaceKHR *out_surface) {
        const auto code = glfwCreateWindowSurface(instance->get(), mWindow, nullptr, out_surface);
        if (code != VK_SUCCESS) {
            out
            .error("failed to create window's surface (vulkan)!")
            .trace("instance=0x%08 out=0x%08", (void*)instance, (void*)out_surface);
        }
    }*/
}
