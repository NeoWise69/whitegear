#include "common.hlsl"

float4 S_Main(pixel_data px) : SV_TARGET {
    return px.vt.color;
}