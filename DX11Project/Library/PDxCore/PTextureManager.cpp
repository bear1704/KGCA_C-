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
			int texture_size = 0;
			std::vector<DX::PTEXTURE_BUF> uv;
			std::vector<std::string> uv_string;
			PTexture* texture; 
			while (true)
			{
				iter++;
				if (iter->first == "tex_name")
					texture_name.assign(iter->second.begin(), iter->second.end());
				else if (iter->first == "texbuf_size")
					texture_size = std::stoi(iter->second);
				else if (iter->first == "tex_path")
					tex_path.assign(iter->second.begin(), iter->second.end());
				else if (iter->first == "uv")
				{
					uv_string = parser.SplitString(iter->second, ',');
					DX::PTEXTURE_BUF buf = { std::stof(uv_string[0]), std::stof(uv_string[1]) };
					uv.push_back(buf);
				}
				else if (iter->first == "END")
					break;
			}

			texture = new PTexture();
			//texture->set_texbuf_size(texture_size);
			//texture->set_texture_buf(std::move(uv));

			ID3D11ShaderResourceView** view = texture->shader_res_view_double_ptr();
			
			
			HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
				current_device, tex_path.c_str(), NULL, NULL, view, NULL
			);

			if (FAILED(hr))
				assert(false); //¿©±â ¿À·ù¶ä

			texture_list_.insert(make_pair(tex_path, texture));


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
	//assert(false);
	return nullptr;
}
