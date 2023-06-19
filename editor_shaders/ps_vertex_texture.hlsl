#include "common.hlsl"

Texture2D albedo_map;
SamplerState texture_sampler;

float4 S_Main(pixel_data px) : SV_TARGET {
    return albedo_map.Sample(texture_sampler, px.vt.texcoord);
}