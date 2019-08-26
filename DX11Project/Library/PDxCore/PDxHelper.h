#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <wrl.h>
#include <assert.h>
#include "PDxState.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

#define OUT_  


namespace DX
{

	struct VECTOR4
	{
		float x;
		float y;
		float z;
		float w;

	};
	struct PVERTEX_TEX
	{
		float posX;
		float posY;
		float posZ;
		float u;
		float v;
	};

	struct PVERTEX
	{
		float poxX;
		float posY;
		float posZ;
	};

	struct PTEXTURE_BUF
	{
		float u;
		float v;
	};

	struct PTextureBufSet
	{
		float u0, u1, u2, u3;
		float v0, v1, v2, v3;
	};



	struct VS_CONSTANT_BUFFER
	{
		VECTOR4 color; //c0
		float time; //c1.x
		float theta; //c1.y
		float z; //c1.z
		float w;  //c1.w
	};

	struct Plane
	{

	};




	//vertices : 버텍스 버퍼 / vertices_struct_size : 버텍스 버퍼에 사용되는 구조체 사이즈 / vertices_count : 버텍스 개수 / PVERTEX_TEX 구조체 사용
	ID3D11Buffer*	CreateVertexBuffer(ID3D11Device* current_device,const void* vertices, int vertices_count, int vertices_struct_size, bool is_dynamic);
	//DWORD 구조체 사용
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* current_device, const void* indices, int indices_count, int indices_struct_size, bool is_dynamic);
	//VS_CONSTANT_BUFFER 구조체 사용
	ID3D11Buffer* CreateConstantBuffer(ID3D11Device* current_device, int constants_struct_size);
	ID3D11VertexShader* LoadVertexShaderFromFile(ID3D11Device* current_device, LPCTSTR vs_file_path, LPCSTR vs_func_name,
		 bool is_already_compiled, OUT_ ID3DBlob** blob = nullptr);
	ID3D11PixelShader* LoadPixelShaderFromFile(ID3D11Device* current_device, LPCTSTR ps_file_path, LPCSTR ps_func_name,
		bool is_already_compiled, OUT_ ID3DBlob** blob = nullptr);
	ID3D11InputLayout* CreateInputLayout(ID3D11Device* current_device, DWORD vs_blob_size, LPCVOID vs_blob_data,
												D3D11_INPUT_ELEMENT_DESC* layout, int element_number);
	PVERTEX_TEX* AssemblyVertAndTex(const PVERTEX* vert, const PTEXTURE_BUF* tex_buf, int size); //나중에 텍스쳐매니져쯤으로 옮겨질 기능 

	class PDxHelper
	{
	public:
		int vertex_count_;
		int index_count_;
		int vertex_size_;

	public:
		Microsoft::WRL::ComPtr<ID3D11Buffer>				vertex_buffer_;
		Microsoft::WRL::ComPtr<ID3D11Buffer>				index_buffer_;
		Microsoft::WRL::ComPtr<ID3D11Buffer>				constant_buffer_;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>			vertex_shader_;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>			pixel_shader_;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>			input_layout_;
		Microsoft::WRL::ComPtr<ID3DBlob>					vertex_blob_;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	shader_res_view_;

		//Render
		void PreRender(ID3D11DeviceContext* context, int stride_length);
		void PostRender(ID3D11DeviceContext* context, int index_count);
		void Render(ID3D11DeviceContext* context);

		void set_shader_res_view(ID3D11ShaderResourceView* view);
	};


} 