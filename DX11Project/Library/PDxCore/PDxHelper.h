#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <wrl.h>
#include <assert.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

namespace DX
{
	//vertices : ���ؽ� ���� / vertices_struct_size : ���ؽ� ���ۿ� ���Ǵ� ����ü ������ / vertices_count : ���ؽ� ���� / PVERTEX_TEX ����ü ���
	ID3D11Buffer*	CreateVertexBuffer(ID3D11Device* current_device,const void* vertices, int vertices_count, int vertices_struct_size, bool is_dynamic);
	//DWORD ����ü ���
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* current_device, const void* indices, int indices_count, int indices_struct_size, bool is_dynamic);
	//VS_CONSTANT_BUFFER ����ü ���
	ID3D11Buffer* CreateConstantBuffer(ID3D11Device* current_device, const void* constants, int constants_count, int constants_struct_size);

	class PDxHelper
	{

	public:
		Microsoft::WRL::ComPtr<ID3D11Buffer>				vertex_buffer_;
		Microsoft::WRL::ComPtr<ID3D11Buffer>				index_buffer_;
		Microsoft::WRL::ComPtr<ID3D11Buffer>				constant_buffer_;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>			vertex_shader_;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>			pixel_shader_;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>			input_layout_;
		Microsoft::WRL::ComPtr<ID3DBlob>					vertex_blob_;


	};


} 