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

	Create(device_, immediate_context_, tex_name, vs_file_path, vs_func_name, ps_file_path, ps_func_name);

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

	PModel::Render();
	return true;
}

HRESULT PPlaneObject::CreateVertexData()
{
	vertex_list_.resize(4);
	vertex_list_[0].pos = DX::Vector3{ -1.0f, 1.0f, 0.5f };
	vertex_list_[1].pos = DX::Vector3{ 1.0f, 1.0f, 0.5f };
	vertex_list_[2].pos = DX::Vector3{ 1.0f,-1.0f, 0.5f };
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

	Create(device_, immediate_context_, tex_name, vs_file_path, vs_func_name, ps_file_path, ps_func_name);

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

	PModel::Render();
	return true;
}

HRESULT PBoxObject::CreateVertexData()
{
	vertex_list_.resize(24);
	vertex_list_[0] = Vertex_PNCT(DX::Vector3(-1.0f, 1.0f, -1.0f), DX::Vector3(0.0f, 0.0f, -1.0f), DX::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	vertex_list_[1] = Vertex_PNCT(DX::Vector3(1.0f, 1.0f, -1.0f), DX::Vector3(0.0f, 0.0f, -1.0f), DX::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	vertex_list_[2] = Vertex_PNCT(DX::Vector3(1.0f, -1.0f, -1.0f), DX::Vector3(0.0f, 0.0f, -1.0f), DX::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	vertex_list_[3] = Vertex_PNCT(DX::Vector3(-1.0f, -1.0f, -1.0f), DX::Vector3(0.0f, 0.0f, -1.0f), DX::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	// �޸�
	vertex_list_[4] = Vertex_PNCT(DX::Vector3(1.0f, 1.0f, 1.0f), DX::Vector3(0.0f, 0.0f, 1.0f), DX::Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	vertex_list_[5] = Vertex_PNCT(DX::Vector3(-1.0f, 1.0f, 1.0f), DX::Vector3(0.0f, 0.0f, 1.0f), DX::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	vertex_list_[6] = Vertex_PNCT(DX::Vector3(-1.0f, -1.0f, 1.0f), DX::Vector3(0.0f, 0.0f, 1.0f), DX::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	vertex_list_[7] = Vertex_PNCT(DX::Vector3(1.0f, -1.0f, 1.0f), DX::Vector3(0.0f, 0.0f, 1.0f), DX::Vector4(0.0f, 1.0f, 0.0f, 1.0f));

	// ������
	vertex_list_[8] = Vertex_PNCT(DX::Vector3(1.0f, 1.0f, -1.0f), DX::Vector3(1.0f, 0.0f, 0.0f), DX::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	vertex_list_[9] = Vertex_PNCT(DX::Vector3(1.0f, 1.0f, 1.0f), DX::Vector3(1.0f, 0.0f, 0.0f), DX::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	vertex_list_[10] = Vertex_PNCT(DX::Vector3(1.0f, -1.0f, 1.0f), DX::Vector3(1.0f, 0.0f, 0.0f), DX::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	vertex_list_[11] = Vertex_PNCT(DX::Vector3(1.0f, -1.0f, -1.0f), DX::Vector3(1.0f, 0.0f, 0.0f), DX::Vector4(0.0f, 0.0f, 1.0f, 1.0f));

	// ����
	vertex_list_[12] = Vertex_PNCT(DX::Vector3(-1.0f, 1.0f, 1.0f), DX::Vector3(-1.0f, 0.0f, 0.0f), DX::Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	vertex_list_[13] = Vertex_PNCT(DX::Vector3(-1.0f, 1.0f, -1.0f), DX::Vector3(-1.0f, 0.0f, 0.0f), DX::Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	vertex_list_[14] = Vertex_PNCT(DX::Vector3(-1.0f, -1.0f, -1.0f), DX::Vector3(-1.0f, 0.0f, 0.0f), DX::Vector4(1.0f, 1.0f, 0.0f, 1.0f));
	vertex_list_[15] = Vertex_PNCT(DX::Vector3(-1.0f, -1.0f, 1.0f), DX::Vector3(-1.0f, 0.0f, 0.0f), DX::Vector4(1.0f, 1.0f, 0.0f, 1.0f));

	// ����
	vertex_list_[16] = Vertex_PNCT(DX::Vector3(-1.0f, 1.0f, 1.0f), DX::Vector3(0.0f, 1.0f, 0.0f), DX::Vector4(1.0f, 0.5f, 1.0f, 1.0f));
	vertex_list_[17] = Vertex_PNCT(DX::Vector3(1.0f, 1.0f, 1.0f), DX::Vector3(0.0f, 1.0f, 0.0f), DX::Vector4(1.0f, 0.5f, 1.0f, 1.0f));
	vertex_list_[18] = Vertex_PNCT(DX::Vector3(1.0f, 1.0f, -1.0f), DX::Vector3(0.0f, 1.0f, 0.0f), DX::Vector4(1.0f, 0.5f, 1.0f, 1.0f));
	vertex_list_[19] = Vertex_PNCT(DX::Vector3(-1.0f, 1.0f, -1.0f), DX::Vector3(0.0f, 1.0f, 0.0f), DX::Vector4(1.0f, 0.5f, 1.0f, 1.0f));

	// �Ʒ���
	vertex_list_[20] = Vertex_PNCT(DX::Vector3(-1.0f, -1.0f, -1.0f), DX::Vector3(0.0f, -1.0f, 0.0f), DX::Vector4(0.0f, 1.0f, 1.0f, 1.0f));
	vertex_list_[21] = Vertex_PNCT(DX::Vector3(1.0f, -1.0f, -1.0f), DX::Vector3(0.0f, -1.0f, 0.0f), DX::Vector4(0.0f, 1.0f, 1.0f, 1.0f));
	vertex_list_[22] = Vertex_PNCT(DX::Vector3(1.0f, -1.0f, 1.0f), DX::Vector3(0.0f, -1.0f, 0.0f), DX::Vector4(0.0f, 1.0f, 1.0f, 1.0f));
	vertex_list_[23] = Vertex_PNCT(DX::Vector3(-1.0f, -1.0f, 1.0f), DX::Vector3(0.0f, -1.0f, 0.0f), DX::Vector4(0.0f, 1.0f, 1.0f, 1.0f));

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
