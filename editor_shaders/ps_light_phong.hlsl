#include "common.hlsl"

float4 S_Main(pixel_data px) : SV_TARGET {
    const float3 normal = px.vt.normal;
    const float3 pos_to_light = light_position - px.vt.position.rgb;
    const float pos_to_light_distance = length(pos_to_light);
    const float3 pos_to_light_direction = pos_to_light / pos_to_light_distance;
    const float attenuation = attenuation_const + attenuation_linear *
                              pos_to_light_distance + attenuation_quadratic *
                              (pos_to_light_distance * pos_to_light_distance);
    const float3 diffuse = albedo_map_color * albedo_map_intensity
                         * attenuation * max(0.0f, dot(pos_to_light_direction, normal));
    return float4(saturate(diffuse + ambient_color), 1.0f);
}