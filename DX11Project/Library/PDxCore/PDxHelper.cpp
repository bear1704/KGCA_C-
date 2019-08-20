#include "PDxHelper.h"

namespace DX
{

	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* current_device, const void* vertices, int vertices_count, int vertices_struct_size, bool is_dynamic)
	{

		D3D11_BUFFER_DESC buffer_desc;
		D3D11_SUBRESOURCE_DATA subresource_data;
		ID3D11Buffer* ret_vertex_buffer;

		ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));
		
		if (is_dynamic)
		{
			buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			buffer_desc.CPUAccessFlags = 0;
		}
		
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.ByteWidth = sizeof(vertices_struct_size) * vertices_count;
		buffer_desc.MiscFlags = 0;
		buffer_desc.StructureByteStride = 0;

		ZeroMemory(&subresource_data, sizeof(D3D11_SUBRESOURCE_DATA));
		
		HRESULT hr;
		if (vertices != nullptr)
		{
			subresource_data.pSysMem = vertices;
			hr = current_device->CreateBuffer(&buffer_desc, &subresource_data, &ret_vertex_buffer); //올려볼까 
		}
		else
		{
			hr = current_device->CreateBuffer(&buffer_desc, NULL, &ret_vertex_buffer); //올려볼까 
		}
		

		if (FAILED(hr))
			assert(false);


		return ret_vertex_buffer;
	}

	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* current_device, const void* indices, int indices_count, int indices_struct_size, bool is_dynamic)
	{
		ID3D11Buffer* ret_index_buffer;

		D3D11_BUFFER_DESC index_buf_desc;
		ZeroMemory(&index_buf_desc, sizeof(D3D11_BUFFER_DESC));

		D3D11_SUBRESOURCE_DATA index_buf_init_data;
		ZeroMemory(&index_buf_init_data, sizeof(D3D11_SUBRESOURCE_DATA));
	

		if (is_dynamic)
		{
			index_buf_desc.Usage = D3D11_USAGE_DYNAMIC;
			index_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			index_buf_desc.Usage = D3D11_USAGE_DEFAULT;
			index_buf_desc.CPUAccessFlags = 0;
		}

		index_buf_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buf_desc.ByteWidth = indices_struct_size * indices_count;
		index_buf_desc.MiscFlags = 0;


		HRESULT hr;

		if (indices != nullptr)
		{
			index_buf_init_data.pSysMem = indices;
			hr = current_device->CreateBuffer(&index_buf_desc, &index_buf_init_data, &ret_index_buffer);
		}
		else
		{
			hr = current_device->CreateBuffer(&index_buf_desc, NULL, &ret_index_buffer);
		}

		if (FAILED(hr))
			assert(false);

		return ret_index_buffer;

	}

	ID3D11Buffer* CreateConstantBuffer(ID3D11Device* current_device, const void* constants, int constants_count, int constants_struct_size)
	{
		ID3D11Buffer* ret_constant_buffer;
		D3D11_BUFFER_DESC constant_buf_desc;
		ZeroMemory(&constant_buf_desc, sizeof(D3D11_BUFFER_DESC));


		constant_buf_desc.ByteWidth = constants_struct_size * constants_count;
		constant_buf_desc.Usage = D3D11_USAGE_DYNAMIC;
		constant_buf_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constant_buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constant_buf_desc.MiscFlags = 0;
		HRESULT hr = current_device->CreateBuffer(&constant_buf_desc, NULL, &ret_constant_buffer);

		if (FAILED(hr))
			assert(false);

		return ret_constant_buffer;
		
	}

	ID3D11VertexShader* LoadVertexShaderFromFile(ID3D11Device* current_device, LPCTSTR vs_file_path,
													LPCSTR vs_func_name, bool is_already_compiled, OUT_ ID3DBlob** blob = nullptr)
	{
		ID3D11VertexShader* ret_vertex_shader;
		HRESULT hr;
		ID3DBlob* v_shader_blob;
		ID3DBlob* error_msg;
		DWORD blob_size = 0;
		LPCVOID blob_data = 0;

		if (is_already_compiled == false)
		{
			hr = D3DX11CompileFromFile(
				vs_file_path, NULL, NULL,
				vs_func_name, "vs_5_0",
				0, 0, NULL, &v_shader_blob, &error_msg, NULL);


			if (FAILED(hr))
			{
				if (error_msg != nullptr)
				{
					OutputDebugStringA((char*)error_msg->GetBufferPointer());
					if (error_msg)  error_msg->Release();
				}
				assert(false);
				return nullptr;
			}
			blob_size = v_shader_blob->GetBufferSize();
			blob_data = v_shader_blob->GetBufferPointer();
		}
		else //컴파일된 binary blob으로 들어올 경우 
		{
			v_shader_blob = *blob;
			if (v_shader_blob == nullptr) return nullptr;

			blob_size = v_shader_blob->GetBufferSize();
			blob_data = v_shader_blob->GetBufferPointer();
		}

		hr = current_device->CreateVertexShader(blob_data, blob_size, NULL, &ret_vertex_shader);

		if (FAILED(hr))
		{
			v_shader_blob->Release();
			return nullptr;
		}

		if (blob == nullptr)
		{
			v_shader_blob->Release();
		}
		else
		{
			*blob = v_shader_blob;
		}


		return nullptr;
	}

}