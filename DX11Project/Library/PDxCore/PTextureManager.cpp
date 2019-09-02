#include "PTextureManager.h"

PTextureManager::~PTextureManager()
{
}

PTextureManager::PTextureManager()
{
}

bool PTextureManager::Init()
{
	return false;
}

bool PTextureManager::Frame()
{
	return false;
}

bool PTextureManager::Render()
{
	return false;
}

bool PTextureManager::Release()
{
	return false;
}

void PTextureManager::LoadTextureFromScript(multibyte_string filepath, ID3D11Device* current_device)
{
	//아즥 1회제한 안걸어놓음

	PParser parser;
	std::vector<std::pair<string, string>> ret_parse;
	std::string str;
	str.assign(filepath.begin(), filepath.end());
	parser.XmlParse(str, &ret_parse);

	for (auto iter = ret_parse.begin(); iter != ret_parse.end(); iter++)
	{

		if (iter->second.compare("Texture") == 0)
		{
			std::wstring texture_name;
			std::wstring tex_path;
			DX::PTex_uv4 uv4;
			PTexture* texture = nullptr;
			float width = 0;
			float height = 0;

			while (true)
			{
				iter++;
				if (iter->first == "tex_name")
					texture_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first == "tex_path")
					tex_path.assign(iter->second.begin(), iter->second.end());
				else if (iter->first == "image_width")
					width = std::stof(iter->second);
				else if (iter->first == "image_height")
					height = std::stof(iter->second);
				else if (iter->first == "uv_ltop")
				{

					std::vector<std::string> uv_string = parser.SplitString(iter->second, ',');

					DX::PTex_uv left_top = ImageCoordinateToTexCoordinate(std::stof(uv_string[0]), std::stof(uv_string[1]),
						width, height);

					iter++;

					uv_string = parser.SplitString(iter->second, ',');
					DX::PTex_uv right_bottom = ImageCoordinateToTexCoordinate(std::stof(uv_string[0]), std::stof(uv_string[1]),
						width, height);
					
					uv4.u[0] = left_top.u;
					uv4.v[0] = left_top.v;
					uv4.u[1] = right_bottom.u;
					uv4.v[1] = left_top.v;
					uv4.u[2] = right_bottom.u;
					uv4.v[2] = right_bottom.v;
					uv4.u[3] = left_top.u;
					uv4.v[3] = right_bottom.v;
					
				}
				else if (iter->first == "END")
					break;
			}

			texture = new PTexture();
			texture->set_uv_coord(uv4);
			texture->SetImageSize(width, height);

			ID3D11ShaderResourceView** view = texture->shader_res_view_double_ptr();
			
			
			HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
				current_device, tex_path.c_str(), NULL, NULL, view, NULL
			);

			if (FAILED(hr))
				assert(false); //여기 오류뜸

			texture_list_.insert(make_pair(texture_name, texture));
		}
	}
}

PTexture* PTextureManager::GetTextureFromMap(std::wstring key)
{
	auto iter = texture_list_.find(key);
	if (iter != texture_list_.end())
	{
		PTexture* data = (*iter).second;
		return data;
	}
	assert(false);
	return nullptr;
}


DX::PTex_uv PTextureManager::ImageCoordinateToTexCoordinate(float x, float y, float image_width, float image_height)
{
	DX::PTex_uv uv;
	ZeroMemory(&uv, sizeof(DX::PTex_uv));
	uv.u = x / image_width;
	uv.v = y / image_height;

	return uv;
}
