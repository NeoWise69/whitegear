#include "common.hlsl"

static float4 get_world_position(float4 local_position) {
    return mul(local_position, mul(model_matrix, mul(view_matrix, projection_matrix)));
}

pixel_data S_Main(vertex_data vt) {
    pixel_data px;
    px.vt = vt;
    px.vt.position = get_world_position(vt.position);
    return px;
}
