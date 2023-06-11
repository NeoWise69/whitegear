#include "common.hlsl"

vs_out S_Main(float4 pos : POSITION, float4 col : COLOR) {
    vs_out vo;

    vo.position = mul(pos, mul(model_matrix, mul(view_matrix, projection_matrix)));
    vo.color = col;

    return vo;
}
