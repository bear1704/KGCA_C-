#pragma once
#include "PDxHelper.h"
#include "PTextureManager.h"
#include <string>

struct VECTOR4
{
	float x;
	float y;
	float z;
	float w;

};
struct Vertex_PNCT
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;
	D3DXVECTOR2 uv;

	bool operator == (const Vertex_PNCT& Vertex)
	{
		if (pos == Vertex.pos && normal == Vertex.normal && color == Vertex.color && uv == Vertex.uv)
			return true;

		return false;
	}

	Vertex_PNCT() {};
	Vertex_PNCT(D3DXVECTOR3 v_pos, D3DXVECTOR3 v_normal, D3DXVECTOR4 v_color, D3DXVECTOR2 v_uv)
	{
		pos = v_pos;  normal = v_normal; color = v_color; uv = v_uv;
	};
	Vertex_PNCT(D3DXVECTOR3 v_pos, D3DXVECTOR3 v_normal, D3DXVECTOR4 v_color)
	{
		pos = v_pos;  normal = v_normal; color = v_color;
	}






};


struct VS_CONSTANT_BUFFER
{
	VECTOR4 color; //c0
	float time; //c1.x
	float theta; //c1.y
	float z; //c1.z
	float w;  //c1.w
};

struct VS_CB_WVP
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;  //����! �̰� D3DXMatrix���µ� ����������������?
	float color[4];
	float etc[4];
};

class PModel
{
public:
	D3DXMATRIX matWorld_;
	D3DXMATRIX matView_;
	D3DXMATRIX matProj_;
	ID3D11Device* device_;
	ID3D11DeviceContext* immediate_context_;
	DX::PDxHelper dx_helper_;
	std::vector<Vertex_PNCT> vertex_list_;
	std::vector<DWORD> index_list_;
	VS_CB_WVP constant_data_;
	PTexture* texture_; //Sprite�� ������� �ʴ� ���� ������Ʈ���� ���Ǵ� �ؽ��� 
	bool be_using_sprite_;

public:
	PModel();
	virtual ~PModel();

public:
	virtual bool Init(ID3D11Device* device, ID3D11DeviceContext* context);
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();


public:
	virtual bool Create(ID3D11Device* device, ID3D11DeviceContext* context,  std::wstring vs_file_path, std::string vs_func_name, 
		std::wstring ps_file_path, std::string ps_func_name, std::wstring tex_name = L"");
	virtual HRESULT CreateVertexData();
	virtual HRESULT CreateIndexData();
	//vertices : ���ؽ� ���� / vertices_struct_size : ���ؽ� ���ۿ� ���Ǵ� ����ü ������ / vertices_count : ���ؽ� ���� / PVertexAndUV ����ü ���
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadTextures(std::wstring tex_name = nullptr);
	virtual HRESULT LoadVertexShaderFromFile(ID3D11Device* current_device, LPCTSTR vs_file_path, LPCSTR vs_func_name,
		bool is_already_compiled, OUT_ ID3DBlob** blob = nullptr);
	virtual HRESULT LoadPixelShaderFromFile(ID3D11Device* current_device, LPCTSTR ps_file_path, LPCSTR ps_func_name,
		bool is_already_compiled, OUT_ ID3DBlob** blob = nullptr);
	virtual HRESULT CreateInputLayout();
	static void ChangeTexValue(OUT_ std::vector<Vertex_PNCT>& vert, const DX::PTex_uv4& tex_buf) noexcept; 

	//setter
	void SetWVPMatrix(D3DXMATRIX* world = nullptr, D3DXMATRIX* view = nullptr, D3DXMATRIX* proj = nullptr);
	void SetVertexListPos(int count, D3DXVECTOR3 vec);
	//getter
	std::vector<Vertex_PNCT>* GetVertexListPointer();
	std::vector<Vertex_PNCT>& vertex_list();
	DX::PDxHelper& dx_helper();

};

