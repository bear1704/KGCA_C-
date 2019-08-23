cbuffer cb0
{
	float4 color : packoffset(c0);
	float time : packoffset(c1.x);
	float theta : packoffset(c1.y);
};


struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float2 t  : TEXCOORD;
};

struct VS_INPUT
{
	float3 p : POSITION;
	float2 t : TEXCOORD;

};

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT Output = (VS_OUTPUT)0;
	//float3 rot_pos = { input.p.x * cos(theta) - input.p.y * sin(theta) , input.p.x * sin(theta) + input.p.y * cos(theta) , input.p.z};
	//float3 vertex_pos = rot_pos* time;
	
	//Output.Position = float4(vertex_pos, 1.0f);
	//Output.Position = rot_pos;

	Output.Position = float4(input.p, 1.0f);
	Output.t = input.t;


	return Output;
}

