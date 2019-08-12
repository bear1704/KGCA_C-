#include "PDevice.h"

PDevice::PDevice()
{
}

PDevice::~PDevice()
{
}

bool PDevice::InitDevice(HWND hwnd, UINT client_width, UINT client_height)
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE

	};

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	HRESULT hr;
	UINT CreateDeviceFlags = 0;
	UINT driver_type_size = ARRAYSIZE(driver_types);
	UINT feature_level_size = ARRAYSIZE(feature_levels);

	CreateSwapChain(hwnd, client_width, client_height);

	for (int type = 0; type < driver_type_size; type++)
	{
		driver_type_ = driver_types[type];

		hr = D3D11CreateDeviceAndSwapChain(
			NULL, driver_type_, NULL,
			CreateDeviceFlags,
			feature_levels,
			feature_level_size,
			D3D11_SDK_VERSION,
			&swap_chain_desc_,
			&swap_chain_,
			&device_,
			&feature_level_,
			&immediate_device_context_);

		if (SUCCEEDED(hr))
		{
			if (feature_level_ < D3D_FEATURE_LEVEL_11_0)
			{
				swap_chain_->Release();
				immediate_device_context_->Release();
				device_->Release();
				continue;
			}
			break;
		}
		
		
	}
	if (FAILED(hr))
		return false;



	return true;
}

bool PDevice::CreateSwapChain(HWND hwnd, UINT client_width, UINT client_height)
{

	
	ZeroMemory(&swap_chain_desc_, sizeof(swap_chain_desc_));
	swap_chain_desc_.BufferCount = 1;
	swap_chain_desc_.OutputWindow = hwnd;
	swap_chain_desc_.Windowed = true;
	swap_chain_desc_.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc_.SampleDesc.Count = 1;
	swap_chain_desc_.BufferDesc.Width = client_width;
	swap_chain_desc_.BufferDesc.Height = client_height;
	swap_chain_desc_.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc_.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc_.BufferDesc.RefreshRate.Denominator = 1;

	return true;
}

bool PDevice::CreateRenderTarget(UINT client_width, UINT client_height)
{

	ID3D11Texture2D* back_buffer;
	HRESULT hr = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& back_buffer);
	if (FAILED(hr)) return false;

	hr = device_->CreateRenderTargetView(back_buffer, NULL, &render_target_view_);
	back_buffer->Release();

	if (FAILED(hr)) return false;

	immediate_device_context_->OMSetRenderTargets(1, &render_target_view_, NULL);

	viewport_.Width = client_width;
	viewport_.Height = client_height;
	viewport_.MinDepth = 0;
	viewport_.MaxDepth = 1;
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	immediate_device_context_->RSSetViewports(1, &viewport_); //�����Ͷ��������� ȭ���� ������ ����
						//�����Ͷ������� ����Ʈ ���� ���� ǥ���� �ȼ��� ã�Ƽ� PS�� �����ش�. 
	return true;
}

bool PDevice::CreateVertexBuffer(const PVERTEX* vertices, int vertices_size)
{
	
	D3D11_BUFFER_DESC buffer_desc;
	D3D11_SUBRESOURCE_DATA subresource_data;

	buffer_desc.ByteWidth = sizeof(PVERTEX) * vertices_size;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;
	buffer_desc.StructureByteStride = 0;

	ZeroMemory(&subresource_data, sizeof(D3D11_SUBRESOURCE_DATA));
	subresource_data.pSysMem = vertices;

	HRESULT hr = device_->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer_); //�÷����� 

	if (SUCCEEDED(hr))
		return true;

	return false;
	
}

bool PDevice::CreateIndexBuffer(const DWORD* indices, int index_size)
{
	D3D11_BUFFER_DESC index_buf_desc;
	index_buf_desc.ByteWidth = sizeof(DWORD) * index_size;
	index_buf_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buf_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buf_desc.CPUAccessFlags = 0;
	index_buf_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA index_buf_init_data;
	ZeroMemory(&index_buf_init_data, sizeof(D3D11_SUBRESOURCE_DATA));
	index_buf_init_data.pSysMem = indices;
	
	HRESULT hr = device_->CreateBuffer(&index_buf_desc, &index_buf_init_data, &index_buffer_);

	if (SUCCEEDED(hr))
		return true;
	else
	{
		assert(false);
		return false;
	}
}

bool PDevice::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC constant_buf_desc;
	constant_buf_desc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	constant_buf_desc.Usage = D3D11_USAGE_DYNAMIC;
	constant_buf_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constant_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constant_buf_desc.MiscFlags = 0;
	HRESULT hr = device_->CreateBuffer(&constant_buf_desc, NULL, &constant_buffer_);
	
	if (SUCCEEDED(hr))
		return true;
	else
		return false;



}

bool PDevice::LoadShaderResourceView(multibyte_string name)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		device_, name.c_str(), NULL, NULL, &shader_res_view_, NULL
	);
	if (FAILED(hr))
		return false;
	else
		return true;
}

bool PDevice::LoadShaderAndInputLayout(LPCTSTR v_shader_path, LPCTSTR ps_shader_path ,LPCSTR v_shader_func_name, LPCSTR ps_shader_func_name)
{
	ID3DBlob* v_shader_blob;
	ID3DBlob* error_msg;

	//vertex shader create
	HRESULT hr = D3DX11CompileFromFile(
		v_shader_path, NULL, NULL,
		v_shader_func_name, "vs_5_0",
		0, 0, NULL, &v_shader_blob, &error_msg, NULL);

	if (FAILED(hr))
		return false;

	device_->CreateVertexShader(v_shader_blob->GetBufferPointer(), v_shader_blob->GetBufferSize(), NULL, &vertex_shader_);

	
	//pixel shader crate
	ID3DBlob* ps_shader_blob;
	
	hr = D3DX11CompileFromFile(
		ps_shader_path, NULL, NULL,
		ps_shader_func_name, "ps_5_0",
		0, 0, NULL, &ps_shader_blob, &error_msg, NULL);

	device_->CreatePixelShader(ps_shader_blob->GetBufferPointer(), ps_shader_blob->GetBufferSize(), NULL,&pixel_shader_);

	//input layout

	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, //�̺κ� �߰� �ʱ��ؼ� �÷�������
	};

	int element_number = sizeof(layout) / sizeof(layout[0]);

	hr = device_->CreateInputLayout(layout, element_number, v_shader_blob->GetBufferPointer(), v_shader_blob->GetBufferSize(), &input_layout_);

	if (FAILED(hr))
		return false;

	return true;
}

bool PDevice::DeviceRelease()
{
	render_target_view_->Release();
	swap_chain_->Release();
	immediate_device_context_->Release();
	device_->Release();


	if (vertex_buffer_)
		vertex_buffer_->Release();
	if (vertex_shader_)
		vertex_shader_->Release();
	if (pixel_shader_)
		pixel_shader_->Release();
	if (input_layout_)
		input_layout_->Release();
	if (constant_buffer_)
		constant_buffer_->Release();
	if (input_layout_)
		input_layout_->Release();
	if (state_solid_frame_)
		state_solid_frame_->Release();
	if (shader_res_view_)
		shader_res_view_->Release();

	vertex_buffer_ = nullptr;
	vertex_shader_ = nullptr;
	pixel_shader_ = nullptr;
	input_layout_ = nullptr;



	return true;
}

bool PDevice::DevicePreRender()
{
	float clearColor[] = { 0.88f, 0.66f, 0.95f, 1.0f };
	immediate_device_context_->ClearRenderTargetView(render_target_view_, clearColor);
	return true;
}

bool PDevice::DeviceRender()
{

	immediate_device_context_->IASetInputLayout(input_layout_);
	immediate_device_context_->VSSetShader(vertex_shader_, NULL, 0);
	immediate_device_context_->PSSetShader(pixel_shader_, NULL, 0);


	UINT stride = sizeof(PVERTEX);
	UINT offset = 0;

	immediate_device_context_->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	immediate_device_context_->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	immediate_device_context_->VSSetConstantBuffers(0, 1, &constant_buffer_);
	immediate_device_context_->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	immediate_device_context_->PSSetShaderResources(0, 1, &shader_res_view_);
	immediate_device_context_->RSSetState(state_solid_frame_);


	//immediate_device_context_->Draw(3, 0);
	immediate_device_context_->DrawIndexed(6, 0, 0);
	swap_chain_->Present(0, 0);
	return true;
}
