#include "PPlaneObject.h"

PPlaneObject::PPlaneObject()
{
}



PPlaneObject::~PPlaneObject()
{
}

bool PPlaneObject::Init()
{
	return false;
}

bool PPlaneObject::DXInit(ID3D11Device* device, ID3D11DeviceContext* context)
{
	device_ = device;
	immdeidate_context_ = context;
	

	dx_helper.vertex_shader_.Attach(DX::LoadVertexShaderFromFile(device_, L"VertexShader.hlsl", "VS", false, dx_helper.vertex_blob_.GetAddressOf()));
	dx_helper.pixel_shader_.Attach(DX::LoadPixelShaderFromFile(device_, L"PixelShader.hlsl", "PS", false));

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
	};

	int element_count = sizeof(layout) / sizeof(layout[0]);

	dx_helper.input_layout_.Attach(
		DX::CreateInputLayout(device_, dx_helper.vertex_blob_->GetBufferSize(), dx_helper.vertex_blob_->GetBufferPointer(),
			layout, element_count));
	
	
	DWORD indices[] =
	{
		0,1,2,
		0,2,3,
	};

	dx_helper.index_count_ = sizeof(indices) / sizeof(indices[0]);
	dx_helper.index_buffer_.Attach(DX::CreateIndexBuffer(device_, indices, sizeof(indices) / sizeof(indices[0]), sizeof(DWORD), false));

	

	DX::VS_CONSTANT_BUFFER cb;
	ZeroMemory(&cb, sizeof(DX::VS_CONSTANT_BUFFER));

	dx_helper.constant_buffer_.Attach(DX::CreateConstantBuffer(device_, sizeof(DX::VS_CONSTANT_BUFFER)));

	
	PTextureManager::GetInstance().LoadTextureFromScript(L"data/tex.txt", device_);
	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/sprite.txt", ObjectLoadType::ETC_SPRITE);
	sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(L"character_move"), 1.0f, 1.0f);
	
	return false;
}


bool PPlaneObject::Frame()
{	
	float elapsed_time = g_fGameTimer;
	float bounded_time = cosf(elapsed_time) * 0.5f + 0.5f;
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	immdeidate_context_->Map(dx_helper.constant_buffer_.Get() , 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	DX::VS_CONSTANT_BUFFER* constant_buf = (DX::VS_CONSTANT_BUFFER*)MappedResource.pData;
	constant_buf->color = DX::VECTOR4{ cosf(elapsed_time), sinf(elapsed_time), 1.0f - cosf(elapsed_time) , 1.0f };

	constant_buf->time = bounded_time;
	constant_buf->theta = elapsed_time;
	immdeidate_context_->Unmap(dx_helper.constant_buffer_.Get(), 0);

	sprite_.Frame();
	return false;
}

bool PPlaneObject::Render(ID3D11DeviceContext* context)
{	

	sprite_.Render(device_, vertices, dx_helper, false);
	dx_helper.Render(context);
	return false;
}


bool PPlaneObject::Release()
{
	return false;
}
