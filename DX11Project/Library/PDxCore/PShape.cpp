#include "PShape.h"

/*            Plane          */
PPlaneObject::PPlaneObject()
{
}

PPlaneObject::~PPlaneObject()
{
}

bool PPlaneObject::Frame()
{
	PModel::Frame();
	sprite_.Frame();
	return true;
}

bool PPlaneObject::Init(ID3D11Device* device, ID3D11DeviceContext* context,
	std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
	std::wstring tex_name, std::wstring sprite_name)
{

	PModel::Init(device, context);

	Create(device_, immediate_context_, vs_file_path, vs_func_name, ps_file_path, ps_func_name, tex_name);

	if (sprite_name.compare(L"") != 0)
	{
		sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(sprite_name), 1.0f, 1.0f);
		be_using_sprite_ = true;
	}
	return true;
}

bool PPlaneObject::Render()
{
	if (be_using_sprite_ == true)
		sprite_.Render(device_, vertex_list_, dx_helper_, false);
	else
	{

		DX::PTex_uv4 uv4 = texture_->uv_coord();
		ChangeTexValue(vertex_list_, uv4);

		int vertices_count = vertex_list_.size();

		dx_helper_.vertex_size_ = sizeof(Vertex_PNCT);
		dx_helper_.vertex_count_ = vertices_count;
		//dx_helper_.vertex_buffer_.Attach(DX::CreateVertexBuffer(device_, &vertex_list_.at(0), vertices_count, sizeof(Vertex_PNCT), false));
		immediate_context_->UpdateSubresource(dx_helper_.vertex_buffer_.Get(),
			0, NULL, &vertex_list_.at(0), 0, 0);
		dx_helper_.shader_res_view_ = texture_->shader_res_view();

	}
		PModel::Render();
	
	return true;
}

HRESULT PPlaneObject::CreateVertexData()
{
	vertex_list_.resize(4);
	vertex_list_[0].pos = D3DXVECTOR3{ -1.0f, 1.0f, 0.5f };
	vertex_list_[1].pos = D3DXVECTOR3{ 1.0f, 1.0f, 0.5f };
	vertex_list_[2].pos = D3DXVECTOR3{ 1.0f,-1.0f, 0.5f };
	vertex_list_[3].pos = D3DXVECTOR3{ -1.0f,-1.0f, 0.5f };

	vertex_list_[0].normal = D3DXVECTOR3{ 0.0f,0.0f, -1.0f };
	vertex_list_[1].normal = D3DXVECTOR3{ 0.0f,0.0f, -1.0f };
	vertex_list_[2].normal = D3DXVECTOR3{ 0.0f,0.0f, -1.0f };
	vertex_list_[3].normal = D3DXVECTOR3{ 0.0f,0.0f, -1.0f };

	vertex_list_[0].color = D3DXVECTOR4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertex_list_[1].color = D3DXVECTOR4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertex_list_[2].color = D3DXVECTOR4{ 1.0f, 0.0f, 0.0f, 1.0f };
	vertex_list_[3].color = D3DXVECTOR4{ 1.0f, 0.0f, 0.0f, 1.0f };

	vertex_list_[0].uv = D3DXVECTOR2{ 0.0f, 0.0f };
	vertex_list_[1].uv = D3DXVECTOR2{ 1.0f, 0.0f };
	vertex_list_[2].uv = D3DXVECTOR2{ 1.0f, 1.0f };
	vertex_list_[3].uv = D3DXVECTOR2{ 0.0f, 1.0f };

	return S_OK;
}

HRESULT PPlaneObject::CreateIndexData()
{
	index_list_.resize(6);
	index_list_[0] = 0; index_list_[1] = 1; index_list_[2] = 2;
	index_list_[3] = 0; index_list_[4] = 2; index_list_[5] = 3;

	return S_OK;
}


/*            Box          */

PBoxObject::PBoxObject()
{
}

PBoxObject::~PBoxObject()
{
}

bool PBoxObject::Init(ID3D11Device* device, ID3D11DeviceContext* context, std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name, std::wstring tex_name, std::wstring sprite_name)
{

	PModel::Init(device, context);

	Create(device_, immediate_context_, vs_file_path, vs_func_name, ps_file_path, ps_func_name, tex_name);

	if (sprite_name.compare(L"") != 0)
	{
		sprite_.Clone(PSpriteManager::GetInstance().get_sprite_from_map_ex(sprite_name), 1.0f, 1.0f);
		be_using_sprite_ = true;
	}
	return true;
}

bool PBoxObject::Frame()
{
	PModel::Frame();
	sprite_.Frame();
	return true;
}

bool PBoxObject::Render()
{
	if (be_using_sprite_ == true)
		sprite_.Render(device_, vertex_list_, dx_helper_, false);


	DX::PTex_uv4 uv4 = texture_->uv_coord();
	ChangeTexValue(vertex_list_, uv4);

	int vertices_count = vertex_list_.size();

	dx_helper_.vertex_size_ = sizeof(Vertex_PNCT);
	dx_helper_.vertex_count_ = vertices_count;
	//dx_helper_.vertex_buffer_.Attach(DX::CreateVertexBuffer(device_, &vertex_list_.at(0), vertices_count, sizeof(Vertex_PNCT), false));
	immediate_context_->UpdateSubresource(dx_helper_.vertex_buffer_.Get(),
		0, NULL, &vertex_list_.at(0), 0, 0);
	dx_helper_.shader_res_view_ = texture_->shader_res_view();


	PModel::Render();
	return true;
}

HRESULT PBoxObject::CreateVertexData()
{
	vertex_list_.resize(24);
	vertex_list_[0] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) , D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[1] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[2] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[3] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	// µÞ¸é
	vertex_list_[4] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, 1.0f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[5] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[6] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[7] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	vertex_list_[8] =  Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[9] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),   D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[10] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[11] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),D3DXVECTOR2(0.0f, 1.0f));

	// ¿ÞÂÊ
	vertex_list_[12] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, 1.0f),   D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[13] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[14] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[15] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// À­¸é
	vertex_list_[16] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[17] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[18] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[19] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¾Æ·§¸é
	vertex_list_[20] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, -1.0f),D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[21] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[22] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[23] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	return S_OK;
}

HRESULT PBoxObject::CreateIndexData()
{
	index_list_.resize(36);
	int iIndex = 0;
	index_list_[iIndex++] = 0; 	index_list_[iIndex++] = 1; 	index_list_[iIndex++] = 2; 	index_list_[iIndex++] = 0;	index_list_[iIndex++] = 2; 	index_list_[iIndex++] = 3;
	index_list_[iIndex++] = 4; 	index_list_[iIndex++] = 5; 	index_list_[iIndex++] = 6; 	index_list_[iIndex++] = 4;	index_list_[iIndex++] = 6; 	index_list_[iIndex++] = 7;
	index_list_[iIndex++] = 8; 	index_list_[iIndex++] = 9; 	index_list_[iIndex++] = 10; index_list_[iIndex++] = 8;	index_list_[iIndex++] = 10; index_list_[iIndex++] = 11;
	index_list_[iIndex++] = 12; index_list_[iIndex++] = 13; index_list_[iIndex++] = 14; index_list_[iIndex++] = 12;	index_list_[iIndex++] = 14; index_list_[iIndex++] = 15;
	index_list_[iIndex++] = 16; index_list_[iIndex++] = 17; index_list_[iIndex++] = 18; index_list_[iIndex++] = 16;	index_list_[iIndex++] = 18; index_list_[iIndex++] = 19;
	index_list_[iIndex++] = 20; index_list_[iIndex++] = 21; index_list_[iIndex++] = 22; index_list_[iIndex++] = 20;	index_list_[iIndex++] = 22; index_list_[iIndex++] = 23;

	return S_OK;
}

PImportObject::PImportObject()
{
}

PImportObject::~PImportObject()
{
}

bool PImportObject::Init(ID3D11Device* device, ID3D11DeviceContext* context, std::wstring vs_file_path, 
	std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name, std::string object_path)
{
	PModel::Init(device, context);
	PParser parse;
	parse.MaxExportParse(info, object_path);

	Create(device_, immediate_context_, vs_file_path, vs_func_name, ps_file_path, ps_func_name);

	return true;
}

HRESULT PImportObject::CreateVertexBuffer()
{
	dx_helper_.vertex_size_ = sizeof(Vertex_PNCT);
	dx_helper_.vertex_count_ = vertices_list_[0].size();
	dx_helper_.vertex_buffer_.Attach(DX::CreateVertexBuffer(device_, &vertices_list_[0].at(0), dx_helper_.vertex_count_,
		dx_helper_.vertex_size_, false));

	return S_OK;
}

HRESULT PImportObject::CreateIndexBuffer()
{

	dx_helper_.index_count_ = indices_list_[0].size();
	dx_helper_.index_buffer_.Attach(DX::CreateIndexBuffer(
		device_, &indices_list_[0].at(0), dx_helper_.index_count_, sizeof(int), false));


	return S_OK;
}

HRESULT PImportObject::CreateVertexData()
{
	vertices_list_.resize(info.submaterial_list_size);
	for (int i = 0; i < info.submaterial_list_size; i++)
	{
		vertices_list_[i] = std::move(info.vertex_list[i]);
	}

	return S_OK;
}

HRESULT PImportObject::CreateIndexData()
{
	indices_list_.resize(info.submaterial_list_size);
	for (int i = 0; i < info.submaterial_list_size; i++)
	{
		indices_list_[i] = std::move(info.index_list[i]);
	}
	
	return S_OK;
}

bool PImportObject::Render()
{
	PreRender();

	//for (int i = 0; i < info.submaterial_list_size; i++)
	//{

	//	int vertices_count = info.numberof_vertices[i];
	//	dx_helper_.vertex_size_ = sizeof(Vertex_PNCT);
	//	dx_helper_.vertex_count_ = vertices_count;
	//	immediate_context_->UpdateSubresource(dx_helper_.vertex_buffer_.Get(),
	//		0, NULL, &vertices_list_[i].at(0), 0, 0);

	//	dx_helper_.index_count_ = info.numberof_indicies[i];
	//	//dx_helper_.shader_res_view_ = texture_->shader_res_view();
	//}
	int vertices_count = info.numberof_vertices[0];
	dx_helper_.vertex_size_ = sizeof(Vertex_PNCT);
	dx_helper_.vertex_count_ = vertices_count;
	immediate_context_->UpdateSubresource(dx_helper_.vertex_buffer_.Get(),
		0, NULL, &vertices_list_[0].at(0), 0, 0);

	dx_helper_.index_count_ = info.numberof_indicies[0];

	PostRender();
	return true;
}
