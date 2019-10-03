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
	// 뒷면
	vertex_list_[4] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, 1.0f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[5] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[6] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[7] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// 오른쪽
	vertex_list_[8] =  Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[9] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),   D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[10] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[11] = Vertex_PNCT(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f),D3DXVECTOR2(0.0f, 1.0f));

	// 왼쪽
	vertex_list_[12] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, 1.0f),   D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[13] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[14] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[15] = Vertex_PNCT(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// 윗면
	vertex_list_[16] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	vertex_list_[17] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	vertex_list_[18] = Vertex_PNCT(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	vertex_list_[19] = Vertex_PNCT(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// 아랫면
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
	std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name, std::wstring object_path, std::wstring texcomp_path)
{
	std::vector<MaxExportInfo> info;
	std::vector<Material> matrl_info;

	PModel::Init(device, context);
	PParser parse;
	parse.MaxExportParse(info, matrl_info, object_path, texcomp_path, device);
	
	object_list_.resize(info.size());
	for (int i = 0; i < info.size(); i++) //오브젝트 정보 이식
	{
		object_list_[i].info = std::move(info[i]);
	}
	material_list_ = std::move(matrl_info); //머터리얼 정보 이식



	Create(device_, immediate_context_, vs_file_path, vs_func_name, ps_file_path, ps_func_name);


	return true;
}

HRESULT PImportObject::CreateVertexBuffer()
{
	for (int obj = 0; obj < object_list_.size(); obj++)
	{
		object_list_[obj].helper_list_.resize(object_list_[obj].info.vertex_list.size());
		
		for (int i = 0; i < object_list_[obj].info.vertex_list.size(); i++)
		{
			auto cur_dxhelper = object_list_[obj].helper_list_[i];
			cur_dxhelper.vertex_size_ = sizeof(Vertex_PNCT);
			cur_dxhelper.vertex_count_ = object_list_[obj].vertices_list_[i].size();
			
			cur_dxhelper.vertex_buffer_.Attach(DX::CreateVertexBuffer(device_,
				&object_list_[obj].vertices_list_[i].at(0),
				cur_dxhelper.vertex_count_, 
				cur_dxhelper.vertex_size_, false));

			if (cur_dxhelper.vertex_buffer_.Get() == nullptr)
				return E_FAIL;
		}
	}
	return S_OK;
}

HRESULT PImportObject::CreateIndexBuffer()
{
	for (int obj = 0; obj < object_list_.size(); obj++)
	{

		for (int i = 0; i < object_list_[obj].info.index_list.size(); i++)
		{
			auto& cur_dxhelper = object_list_[obj].helper_list_[i];
			cur_dxhelper.index_count_ = object_list_[obj].indices_list_[i].size();
			cur_dxhelper.index_buffer_.Attach(DX::CreateIndexBuffer(device_,
				&object_list_[obj].indices_list_[i].at(0),
				cur_dxhelper.index_count_,
				sizeof(int),false));

			if (cur_dxhelper.index_buffer_.Get() == nullptr)
				return E_FAIL;
		}
	}
	return S_OK;
}

HRESULT PImportObject::CreateVertexData()
{
	int object_size = object_list_.size();

	for (int obj = 0; obj < object_size; obj++)
	{
		auto& cur_object = object_list_[obj];
		cur_object.vertices_list_.resize(cur_object.info.vertex_list.size());
		for (int i = 0; i < cur_object.info.vertex_list.size(); i++)
		{
			cur_object.vertices_list_[i] = std::move(cur_object.info.vertex_list[i]);
		}
	}
	return S_OK;
}

HRESULT PImportObject::CreateIndexData()
{
	int object_size = object_list_.size();

	for (int obj = 0; obj < object_size; obj++)
	{
		auto& cur_object = object_list_[obj];
		cur_object.indices_list_.resize(cur_object.info.index_list.size());
		for (int i = 0; i < cur_object.info.index_list.size(); i++)
		{
			cur_object.indices_list_[i] = std::move(cur_object.info.index_list[i]);
		}
	}
	return S_OK;
}

bool PImportObject::PostRender()
{
	for (int obj = 0; obj < object_list_.size(); obj++)
	{
		int root_index = object_list_[obj].info.meshinfo.material_id;
		if (root_index >= 0 && material_list_[root_index].sub_material_list.size() > 0)
		{
			for (int submatl = 0; submatl < object_list_[obj].info.meshinfo.numberof_submesh; submatl++)
			{
				std::wstring key = material_list_[root_index].sub_material_list[submatl].own_material_texname;
				immediate_context_->PSSetShaderResources(0, 1, PTextureManager::GetInstance().GetTextureFromMap(key)->shader_res_view_double_ptr());

				UINT stride = object_list_[obj].helper_list_[submatl].vertex_count_;
				UINT offset = 0;

				immediate_context_->IASetVertexBuffers(0, 1, object_list_[obj].helper_list_[submatl].vertex_buffer_.GetAddressOf(),
					&stride, &offset);

				immediate_context_->IASetIndexBuffer(object_list_[obj].helper_list_[submatl].index_buffer_.Get(),
					DXGI_FORMAT_R32_UINT, 0);

				immediate_context_->DrawIndexed(object_list_[obj].indices_list_[submatl].size(), 0, 0);

			}	

		}
		else
		{
			immediate_context_->PSSetShaderResources(0, 1, dx_helper_.shader_res_view_.GetAddressOf());
			UINT stride = dx_helper_.vertex_size_;
			if (stride <= 0)
				assert(false);
			UINT offset = 0;

			immediate_context_->IASetVertexBuffers(0, 1, dx_helper_.vertex_buffer_.GetAddressOf(), 
				&stride, &offset);
			immediate_context_->IASetIndexBuffer(dx_helper_.index_buffer_.Get(),
				DXGI_FORMAT_R32_UINT, 0);

			immediate_context_->DrawIndexed(index_list_.size(), 0, 0);
		}



	}


	return true;
}

