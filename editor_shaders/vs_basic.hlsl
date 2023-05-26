#include "common.hlsl"

vs_out S_Main(float4 pos : POSITION, float4 col : COLOR) {
    vs_out vo;

    vo.position = mul(pos, model_matrix);
    vo.color = col;

    return vo;
}
