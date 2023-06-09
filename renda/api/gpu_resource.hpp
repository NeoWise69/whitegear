
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#ifndef WHITEGEAR_GPU_RESOURCE_HPP
#define WHITEGEAR_GPU_RESOURCE_HPP

#include <renda/api/common.hpp>
#include <renda/api/gpu_device.hpp>

namespace wg::renda {
    class gpu_resource : public ref_counted {
    public:
        inline virtual ~gpu_resource() noexcept = default;
        inline gpu_resource() noexcept = default;
        inline gpu_resource(e_gpu_resource_type type) noexcept : resource_type(type) {}
        virtual void bind(gpu_device& device) const noexcept {}

        inline e_gpu_resource_type get_resource_type() const {
            return resource_type;
        }
    protected:
        e_gpu_resource_type resource_type = GPU_RESOURCE_UNKNOWN;
    };

    class topology : public gpu_resource {
    public:
        inline topology(e_topology t) noexcept : topo(t), gpu_resource(GPU_RESOURCE_TOPOLOGY)
        {}
        void bind(gpu_device& device) const noexcept override;
    private:
        e_topology topo = TOPOLOGY_NONE;
    };

    class geometry_buffer : public gpu_resource {
    public:
        struct create_info {
            uint count = {};
            memory_data_t memory = {};
        };
        inline geometry_buffer() noexcept = default;
        ~geometry_buffer() override;

        geometry_buffer(const gpu_device& device, e_buffer_type type, const create_info& ci, const vertex_layout* layout = (vertex_layout*)nullptr) noexcept;

        void bind(gpu_device& device) const noexcept override;

        inline i_object get_handle() const noexcept  { return handle; }
        inline uint get_count() const noexcept { return num; }
    private:
        e_buffer_type type = BUFFER_TYPE_NONE;
        i_object handle = nullptr;
        uint num = {};
    };

    enum e_shader_type : uint {
        SHADER_TYPE_NONE,
        SHADER_TYPE_VERTEX_SHADER,
        SHADER_TYPE_PIXEL_SHADER,
    };

    class shader_program : public gpu_resource {
    public:
        inline shader_program() noexcept = default;
        ~shader_program() noexcept override;

        shader_program(const gpu_device& device, e_shader_type type, const string_view& filename) noexcept;

        void bind(gpu_device& device) const noexcept override;

        inline i_object get_code() const noexcept {
            return code;
        }
    private:
        e_shader_type type = SHADER_TYPE_NONE;
        i_object handle = nullptr;
        i_object code = nullptr;
    };

    class vertex_input_layout : public gpu_resource {
    public:
        inline vertex_input_layout() noexcept = default;
        ~vertex_input_layout() noexcept override;

        vertex_input_layout(const gpu_device& device, const vertex_layout& vl, i_object vs_code) noexcept;

        void bind(gpu_device& device) const noexcept override;
    private:
        i_object handle = nullptr;
    };

    class constant_buffer : public gpu_resource {
    public:
        inline constant_buffer() noexcept = default;
        ~constant_buffer() noexcept override;

        constant_buffer(const gpu_device& device, const memory_data_t& mem, e_bind_target tar = BIND_TARGET_VERTEX_SHADER_STAGE) noexcept;

        void update(gpu_device& device, const void* p_data) const noexcept;
        void bind(gpu_device& device) const noexcept override;
        void bind(gpu_device& device, uint start_slot) const noexcept;
    private:
        i_object handle = nullptr;
        e_bind_target target = BIND_TARGET_NONE;
        uint size = {};
    };

}

#endif //WHITEGEAR_GPU_RESOURCE_HPP
