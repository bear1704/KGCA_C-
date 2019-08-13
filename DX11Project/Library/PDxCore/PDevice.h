#pragma once
#include <assert.h>
#include "PWindow.h"
#include "PStd.h"
#include <memory>
#include <d3d11.h>
#include <d3dx11.h>

class PTexture;

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#define OUT_  

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


struct VS_CONSTANT_BUFFER
{
	VECTOR4 color; //c0
	float time; //c1.x
	float theta; //c1.y
	float z; //c1.z
	float w;  //c1.w
};

class PDevice : public PWindow
{
public:
	PDevice();
	~PDevice();

protected:
	
	DXGI_SWAP_CHAIN_DESC	swap_chain_desc_;
	D3D_DRIVER_TYPE			driver_type_;
	D3D_FEATURE_LEVEL		feature_level_;
	IDXGISwapChain*			swap_chain_;
	ID3D11Device*			device_;
	ID3D11DeviceContext*	immediate_device_context_;
	ID3D11RenderTargetView* render_target_view_;
	D3D11_VIEWPORT			viewport_;

	D3D_DRIVER_TYPE driver_types[3];
	D3D_FEATURE_LEVEL feature_levels[2];

	ID3D11Buffer*			vertex_buffer_; //버텍스 버퍼
	ID3D11InputLayout*		input_layout_; //입력 레이아웃
	ID3D11Buffer*			index_buffer_;
	ID3D11Buffer*			constant_buffer_;

	ID3D11VertexShader*		vertex_shader_;
	ID3D11PixelShader*		pixel_shader_;

	ID3D11ShaderResourceView* shader_res_view_;
	ID3D11RasterizerState* state_solid_frame_;



public:
	bool		InitDevice(HWND hwnd, UINT client_width, UINT client_height);
	bool		CreateSwapChain(HWND hwnd, UINT client_width, UINT client_height);
	bool		CreateRenderTarget(UINT client_width, UINT client_height);
	bool		CreateVertexBuffer(const PVERTEX_TEX* vertices, int vertices_size);
	bool		CreateIndexBuffer(const DWORD* indices, int index_size);
	bool		CreateConstantBuffer();
	bool		LoadShaderResourceView(multibyte_string name, OUT_ ID3D11ShaderResourceView* view);
	bool		LoadShaderAndInputLayout(LPCTSTR v_shader_path, LPCTSTR ps_shader_path,LPCSTR v_shader_func_name, LPCSTR ps_shader_func_name);
				//Layout이 들어가야할듯
	bool		DevicePreRender();
	bool		DeviceRender();
	bool		DeviceRelease();

	PVERTEX_TEX* AssemblyVertAndTex(const PVERTEX* vert, const PTEXTURE_BUF* tex_buf, int size); //나중에 텍스쳐매니져쯤으로 옮겨질 기능 



};

