#pragma pack_matrix(row_major)

struct vertex_data {
    float4 position     : SV_POSITION;
    float2 texcoord     : TEXCOORD;
    float4 color        : COLOR;
    float3 normal       : NORMAL;
    float3 tangent      : TANGENT;
    float3 bitangent    : BITANGENT;
};

struct pixel_data {
    vertex_data vt;
};

cbuffer material_data_t {
	float4x4 model_matrix;
};

cbuffer frame_data_t {
    float4x4 projection_matrix;
    float4x4 view_matrix;
};