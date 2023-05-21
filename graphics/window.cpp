
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <graphics/window.hpp>
#include <graphics/cursor.hpp>

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

        glfwSetKeyCallback(tmp, [](GLFWwindow*, int _key, int, int action, int) {
            auto& kbd = input::get().get_keyboard();
            auto& kbd_state = kbd.get_state();
            kbd_state.source = IDEVICE_KEYBOARD;
            switch (action) {
                case GLFW_REPEAT:
                case GLFW_PRESS: {
                    kbd_state.keys[_key] = KEY_STATE_PRESSED;
                    break;
                }
                case GLFW_RELEASE: {
                    kbd_state.keys[_key] = KEY_STATE_RELEASED;
                    kbd_state.release_keys.emplace_back(key(_key));
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(tmp, [](GLFWwindow* window, int button, int action, int mods) {
            auto& ms = input::get().get_mouse();
            auto& ms_state = ms.get_state();
            ms_state.source = IDEVICE_MOUSE;
            switch (action) {
                case GLFW_REPEAT:
                case GLFW_PRESS: {
                    ms_state.keys[button] = KEY_STATE_PRESSED;
                    break;
                }
                case GLFW_RELEASE: {
                    ms_state.keys[button] = KEY_STATE_RELEASED;
                    ms_state.release_keys.emplace_back(key(button));
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetCursorPosCallback(tmp, [](GLFWwindow*, double xpos, double ypos) {
            auto& ms = input::get().get_mouse();
            auto& ms_state = ms.get_state();
            ms_state.source = IDEVICE_MOUSE;
            ms_state.value = {float(xpos), float(ypos), 0.0f};
        });

        // TODO: configurable cursor
        { // Setup default cursor.
            constexpr auto cursor_size = 24;
            color32 cursor_pixels[cursor_size * cursor_size] = {};
            get_cursor(cursor_pixels, CURSOR_DEFAULT, CURSOR_STATE_NORMAL);
            u8* raw_cursor_pixels = (u8*)cursor_pixels;

            GLFWimage cursor_image = {};
            cursor_image.width = cursor_size;
            cursor_image.height = cursor_size;
            cursor_image.pixels = raw_cursor_pixels;

            GLFWcursor* cursor = glfwCreateCursor(&cursor_image, 0, 0);
            glfwSetCursor(tmp, cursor);
        }

        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(tmp, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }

        mWindow = tmp;
        mInfo.alive = true;

        out
        .trace("window[%s, %dx%d] has been created.", p_info->title.c_str(), p_info->w, p_info->h)
        ;
    }

    void window::platform_update() {
        auto& kbd = input::get().get_keyboard();
        auto& ms = input::get().get_mouse();
        kbd.process_release_keys();
        ms.process_release_keys();

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
