#include "PDxRenderTarget.h"

HRESULT PDxRenderTarget::Create(ID3D11Device* device, float width, float height)
{
	D3D11_TEXTURE2D_DESC td; //�ؽ��� ����
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; //����Ÿ�� 
	td.ArraySize = 1;

	device->CreateTexture2D(&td, NULL, texture_.GetAddressOf());
	device->CreateShaderResourceView(texture_.Get(), NULL, shader_res_view_.GetAddressOf());
	device->CreateRenderTargetView(texture_.Get(), NULL, render_target_view_.GetAddressOf());



	//DS    
	td.Format = depthstencil_format_;
	
	//�Ϲ� ���̸�
	if(td.Format == DXGI_FORMAT_D24_UNORM_S8_UINT)
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	else //�����ε��� ���̸�
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

	//td.CPUAccessFlags = 0;
	//td.MiscFlags = 0;

	device->CreateTexture2D(&td, NULL, depth_stencil_texture_.GetAddressOf());

	//ds_view = ���̸ʿ� �̿�Ǵ� DSView ��ũ����  , sr_view_desc = ���̸� �׸��ڿ� ���Ǵ� DsView ��ũ����
	D3D11_DEPTH_STENCIL_VIEW_DESC ds_view_desc;
	D3D11_SHADER_RESOURCE_VIEW_DESC sr_view_desc;

	ZeroMemory(&ds_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ZeroMemory(&sr_view_desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	ds_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	switch (td.Format)
	{   //r32 = ������� ���̸�
	case DXGI_FORMAT_R32_TYPELESS:
		ds_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
		sr_view_desc.Format = DXGI_FORMAT_R32_FLOAT;
		is_depth_shadow_rt_ = true;
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		ds_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		sr_view_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	}


	device->CreateDepthStencilView(
		depth_stencil_texture_.Get(), &ds_view_desc,
		depth_stencil_view_.GetAddressOf());

	viewport_.Height = height;
	viewport_.Width = width;
	viewport_.MaxDepth = 1;
	viewport_.MinDepth = 0;
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;

	if (td.Format == DXGI_FORMAT_R32_TYPELESS)
	{
		sr_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sr_view_desc.Texture2D.MostDetailedMip = 0;
		sr_view_desc.Texture2D.MipLevels = 1;
		device->CreateShaderResourceView(texture_.Get(), &sr_view_desc, &depth_stencil_shader_res_view_);
	}
	depth_stencil_view_->GetDesc(&depthstencil_desc_);

	return S_OK;
}

bool PDxRenderTarget::Begin(ID3D11DeviceContext* context)
{
	ID3D11RenderTargetView* temp_rtv[1] = { 0 };

	numberof_view_port_ = 1;
	context->RSGetViewports(&numberof_view_port_, &viewport_old_);
	context->OMGetRenderTargets(1, render_target_view_old_.GetAddressOf(),
		depth_stencil_view_old_.GetAddressOf());

	if (!is_depth_shadow_rt_)
	{
		context->OMSetRenderTargets(1,
			render_target_view_.GetAddressOf(),
			depth_stencil_view_.Get());

		context->ClearRenderTargetView(
			render_target_view_.Get(), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	else //�������� �����쿡�� ����� ���̹Ƿ� �ٸ� ����Ÿ�ٿ� �׸��� �ʾƵ� �ȴ�
	{
		context->OMSetRenderTargets(1, temp_rtv, depth_stencil_view_.Get());		
	}


	context->RSSetViewports(1, &viewport_);

	context->ClearDepthStencilView(
		depth_stencil_view_.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return true;
}

bool PDxRenderTarget::End(ID3D11DeviceContext* context)
{
	context->RSSetViewports(numberof_view_port_, &viewport_old_);
	context->OMSetRenderTargets(1, render_target_view_old_.GetAddressOf(),
		depth_stencil_view_old_.Get());

	render_target_view_old_.Reset();
	depth_stencil_view_old_.Reset();
	
	return true;
}

bool PDxRenderTarget::Release()
{
	return true;
}

PDxRenderTarget::PDxRenderTarget()
{
	depthstencil_format_ = DXGI_FORMAT_D24_UNORM_S8_UINT;
	is_depth_shadow_rt_ = false;
}

PDxRenderTarget::~PDxRenderTarget()
{
}
