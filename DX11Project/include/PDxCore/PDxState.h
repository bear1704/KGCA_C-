#pragma once
#include <d3dx11.h>
#include <memory>
#include <assert.h>

namespace DX
{

	class PDxState
	{
	public:
		static ID3D11BlendState* blend_state_alphablend_;
		static ID3D11BlendState* blend_state_alphablend_disable_;

		static ID3D11RasterizerState* rs_state_wireframe_;
		static ID3D11RasterizerState* rs_state_solidframe_;

		static void SetState(ID3D11Device* current_device);
		static void Release();

	public:
		PDxState();
		~PDxState();


	};


	static void ApplyRasterizerState(ID3D11DeviceContext* context, ID3D11RasterizerState* state)
	{
		context->RSSetState(state);
	};
	static void ApplyBlendState(ID3D11DeviceContext* context, ID3D11BlendState* state, const FLOAT blend_factor[] = 0, UINT mask = 0xffffffff)
	{
		context->OMSetBlendState(state, blend_factor, mask);
	};



}