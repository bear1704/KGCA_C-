#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <wrl.h>
#include <assert.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

namespace DX
{
	//vertices : 버텍스 버퍼 / vertices_struct_size : 버텍스 버퍼에 사용되는 구조체 사이즈 / vertices_count : 버텍스 개수 / PVERTEX_TEX 구조체 사용
	ID3D11Buffer*	CreateVertexBuffer(ID3D11Device* current_device,const void* vertices, int vertices_count, int vertices_struct_size, bool is_dynamic);
	//DWORD 구조체 사용
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* current_device, const void* indices, int indices_count, int indices_struct_size, bool is_dynamic);
	//VS_CONSTANT_BUFFER 구조체 사용
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