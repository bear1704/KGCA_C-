#include "PDxState.h"


namespace DX
{
	ID3D11BlendState* PDxState::blend_state_alphablend_ = 0;
	ID3D11BlendState* PDxState::blend_state_alphablend_disable_ = 0;
	ID3D11RasterizerState* PDxState::rs_state_wireframe_ = 0;
	ID3D11RasterizerState* PDxState::rs_state_solidframe_ = 0;

	void DX::PDxState::SetState(ID3D11Device* current_device)
	{
		if (!current_device) return;

		HRESULT hr;

#pragma region BLEND
		D3D11_BLEND_DESC blend_desc;
		ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));
		blend_desc.AlphaToCoverageEnable = TRUE;
		blend_desc.IndependentBlendEnable = TRUE;
		blend_desc.RenderTarget[0].BlendEnable = TRUE;
		blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		
		blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		hr = current_device->CreateBlendState(&blend_desc, &blend_state_alphablend_);
		if (FAILED(hr))
			assert(false);

		blend_desc.RenderTarget[0].BlendEnable = FALSE;

		hr = current_device->CreateBlendState(&blend_desc, &blend_state_alphablend_);
		if (FAILED(hr))
			assert(false);

		

		
#pragma endregion	BLEND

#pragma region Rasterizer

		D3D11_RASTERIZER_DESC raster_desc;
		ZeroMemory(&raster_desc, sizeof(raster_desc));
		raster_desc.DepthClipEnable = TRUE;
		raster_desc.FillMode = D3D11_FILL_WIREFRAME;
		raster_desc.CullMode = D3D11_CULL_NONE;

		hr = current_device->CreateRasterizerState(&raster_desc, &rs_state_wireframe_);
		if (FAILED(hr))
			return;

		raster_desc.FillMode = D3D11_FILL_SOLID;

		hr = current_device->CreateRasterizerState(&raster_desc, &rs_state_solidframe_);

		if (FAILED(hr))
			return;


#pragma endregion Rasterizer


	}

	void PDxState::Release()
	{
		if (blend_state_alphablend_)
			blend_state_alphablend_->Release();
		if (blend_state_alphablend_disable_)
			blend_state_alphablend_disable_->Release();

		if (rs_state_wireframe_)
			rs_state_wireframe_->Release();
		if (rs_state_solidframe_)
			rs_state_solidframe_->Release();

		rs_state_solidframe_ = 0;
		rs_state_wireframe_ = 0;
		blend_state_alphablend_ = 0;
		blend_state_alphablend_disable_ = 0;
	}

	DX::PDxState::PDxState()
	{
	}

	DX::PDxState::~PDxState()
	{
		Release();
	}
}
