
float4 S_Main(float3 pos : POSITION) : SV_POSITION {
    return float4(pos.x, pos.y, pos.z, 1.0f);
}
