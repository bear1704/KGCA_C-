#include "PPlaneObject.h"

PPlaneObject::PPlaneObject()
{
}

PPlaneObject::~PPlaneObject()
{
}

//bool PPlaneObject::DXInit(ID3D11Device* device, ID3D11DeviceContext* context)
//{
//	device_ = device;
//	immediate_context_ = context;
//	
//
//	dx_helper_.vertex_shader_.Attach(DX::LoadVertexShaderFromFile(device_, L"VertexShader.hlsl", "VS", false, dx_helper_.vertex_blob_.GetAddressOf()));
//	dx_helper_.pixel_shader_.Attach(DX::LoadPixelShaderFromFile(device_, L"PixelShader.hlsl", "PS", false));
//
//	D3D11_INPUT_ELEMENT_DESC layout[] =
//	{
//		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
//		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
//	};
//
//	int element_count = sizeof(layout) / sizeof(layout[0]);
//
//	dx_helper_.input_layout_.Attach(
//		DX::CreateInputLayout(device_, dx_helper_.vertex_blob_->GetBufferSize(), dx_helper_.vertex_blob_->GetBufferPointer(),
//			layout, element_count));
//	
//	
//	DWORD indices[] =
//	{
//		0,1,2,
//		0,2,3,
//	};
//
//	dx_helper_.index_count_ = sizeof(indices) / sizeof(indices[0]);
//	dx_helper_.index_buffer_.Attach(DX::CreateIndexBuffer(device_, indices, sizeof(indices) / sizeof(indices[0]), sizeof(DWORD), false));
//
//	
//
//	DX::VS_CONSTANT_BUFFER cb;
//	ZeroMemory(&cb, sizeof(DX::VS_CONSTANT_BUFFER));
//
//	dx_helper_.constant_buffer_.Attach(DX::CreateConstantBuffer(device_, sizeof(DX::VS_CONSTANT_BUFFER)));
//
//	
//	PTextureManager::GetInstance().LoadTextureFromScript(L"data/tex.txt", device_);
//	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/sprite.txt", ObjectLoadType::ETC_SPRITE);
//	sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(L"character_move"), 1.0f, 1.0f);
//	
//	return false;
//}


bool PPlaneObject::Frame()
{	
	//float elapsed_time = g_fGameTimer;
	//float bounded_time = cosf(elapsed_time) * 0.5f + 0.5f;
	//D3D11_MAPPED_SUBRESOURCE MappedResource;
	//immdeidate_context_->Map(dx_helper_.constant_buffer_.Get() , 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	//DX::VS_CONSTANT_BUFFER* constant_buf = (DX::VS_CONSTANT_BUFFER*)MappedResource.pData;
	//constant_buf->color = DX::VECTOR4{ cosf(elapsed_time), sinf(elapsed_time), 1.0f - cosf(elapsed_time) , 1.0f };

	//constant_buf->time = bounded_time;
	//constant_buf->theta = elapsed_time;
	//immdeidate_context_->Unmap(dx_helper_.constant_buffer_.Get(), 0);
	PModel::Frame();
	sprite_.Frame();
	return false;
}

bool PPlaneObject::Init(ID3D11Device* device, ID3D11DeviceContext* context, 
	std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name ,
	std::wstring tex_name, std::wstring sprite_name)
{

	PModel::Init(device, context);
	//PTextureManager::GetInstance().LoadTextureFromScript(L"data/tex.txt", device_);
	//PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/sprite.txt", ObjectLoadType::ETC_SPRITE);

	Create(device_, immediate_context_, tex_name,vs_file_path, vs_func_name, ps_file_path, ps_func_name);
	
	if (sprite_name.compare(L"") != 0)
	{
		sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(sprite_name), 1.0f, 1.0f);
		be_using_sprite_ = true;
	}
	return true;
}

bool PPlaneObject::Render()
{	
	if(be_using_sprite_ == true)
		sprite_.Render(device_, vertex_list_, dx_helper_, false);
	
	PModel::Render();
	
	return false;
}


HRESULT PPlaneObject::CreateVertexData()
{

	vertex_list_.resize(4);
	vertex_list_[0].pos = DX::Vector3{ -1.0f, 1.0f, 0.5f };
	vertex_list_[1].pos = DX::Vector3{  1.0f, 1.0f, 0.5f };
	vertex_list_[2].pos = DX::Vector3{  1.0f,-1.0f, 0.5f };
	vertex_list_[3].pos = DX::Vector3{ -1.0f,-1.0f, 0.5f };

	vertex_list_[0].normal = DX::Vector3{ 0.0f,0.0f, -1.0f };
	vertex_list_[1].normal = DX::Vector3{ 0.0f,0.0f, -1.0f };
	vertex_list_[2].normal = DX::Vector3{ 0.0f,0.0f, -1.0f };
	vertex_list_[3].normal = DX::Vector3{ 0.0f,0.0f, -1.0f };
	
	vertex_list_[0].color = DX::Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertex_list_[1].color = DX::Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertex_list_[2].color = DX::Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertex_list_[3].color = DX::Vector4{ 1.0f, 0.0f, 0.0f, 1.0f };

	return S_OK;
}

HRESULT PPlaneObject::CreateIndexData()
{
	index_list_.resize(6);
	index_list_[0] = 0; index_list_[1] = 1; index_list_[2] = 2;
	index_list_[3] = 0; index_list_[4] = 2; index_list_[5] = 3;

	return S_OK;
}
