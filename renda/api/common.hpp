
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_COMMON_HPP
#define WHITEGEAR_COMMON_HPP

#include <core/required.hpp>
#include <core/containers/bounded_array.hpp>
#include <math/vertex.hpp>
#include <initializer_list>

namespace wg::renda {
    struct display_info {
        uint hz_numerator = {};
        uint hz_denominator = {};
        uint screen_width = {};
        uint screen_height = {};
    };
    enum e_gpu_resource_type : uint {
        GPU_RESOURCE_UNKNOWN                = 0x00000000,
        GPU_RESOURCE_TOPOLOGY               = 0x00000001,
        GPU_RESOURCE_GEOMETRY_BUFFER        = 0x00000010,
        GPU_RESOURCE_VERTEX_BUFFER          = 0x00000011,
        GPU_RESOURCE_INDEX_BUFFER           = 0x00000012,
        GPU_RESOURCE_SHADER_PROGRAM         = 0x00000100,
        GPU_RESOURCE_VERTEX_PROGRAM         = 0x00000110,
        GPU_RESOURCE_PIXEL_PROGRAM          = 0x00000111,
        GPU_RESOURCE_VERTEX_INPUT_LAYOUT    = 0x00001000,
        GPU_RESOURCE_CONSTANT_BUFFER        = 0x00010000,
        GPU_RESOURCE_VERTEX_CONSTANT_BUFFER = 0x00011000,
        GPU_RESOURCE_PIXEL_CONSTANT_BUFFER  = 0x00011100,
        GPU_RESOURCE_TEXTURE                = 0x00100000,
    };
    enum e_topology : uint {
        TOPOLOGY_NONE           = 0x00000000,
        TOPOLOGY_TRIANGLE_LIST  = 0x00000010,
        TOPOLOGY_TRIANGLE_STRIP = 0x00000100,
        TOPOLOGY_LINE_LIST      = 0x00001000,
    };
    enum e_attribute_rate : uint {
        ATTRIBUTE_PER_VERTEX,
        ATTRIBUTE_PER_INSTANCE,
    };
    struct vertex_layout {
        struct attribute {
            const char* semantic_name;
            e_format format;
            i32 offset; // -1 will automatically count offset for every attribute.
            e_attribute_rate attribute_rate;
            uint step_rate;

            inline attribute(const char* sem_name, e_format f, i32 off = -1, e_attribute_rate rate = ATTRIBUTE_PER_VERTEX, uint instance_step_rate = 0)
                : semantic_name(sem_name), format(f), offset(off), attribute_rate(rate), step_rate(instance_step_rate)
            {}
        };

        inline vertex_layout(const std::initializer_list<attribute>& list) : attributes(list) {
            calculate_attribute_offsets();
        }

        static vertex_layout create_for(vertex_type type);

        bounded_array<attribute, 16> attributes = {};
        uint vertex_size = {};
    private:
        void calculate_attribute_offsets();
    };
    enum e_buffer_type : uint {
        BUFFER_TYPE_NONE,
        BUFFER_TYPE_VERTEX_BUFFER,
        BUFFER_TYPE_INDEX_BUFFER,
    };
    struct memory_data_t {
        const void* p_memory = nullptr;
        uint size = {};
    };
    enum e_bind_target : uint {
        BIND_TARGET_NONE,
        BIND_TARGET_VERTEX_SHADER_STAGE,
        BIND_TARGET_PIXEL_SHADER_STAGE,
    };
}

#endif //WHITEGEAR_COMMON_HPP
