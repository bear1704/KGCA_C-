Texture2D g_tex_diffuse : register(t0);
SamplerState s0 : register(s0);

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float2 t  : TEXCOORD0;
};

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return g_tex_diffuse.Sample(s0, input.t);

}

