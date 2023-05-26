struct vs_out {
    float4 color : COLOR;
    float4 position : SV_POSITION;
};

cbuffer material_data_t {
	row_major float4x4 model_matrix;
};