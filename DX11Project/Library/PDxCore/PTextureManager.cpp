#include "PTextureManager.h"

PTextureManager::~PTextureManager()
{
}

PTextureManager::PTextureManager()
{
}

void PTextureManager::LoadTextureFromScript(multibyte_string filepath)
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
			int texture_size;
			std::vector<PTEXTURE_BUF> uv;
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
					uv.push_back(PTEXTURE_BUF{ std::stof(uv_string[0]), std::stof(uv_string[1]) });
				}
				else if (iter->first == "END")
					break;
			}

			texture = new PTexture();
			texture->set_texbuf_size = texture_size;
			texture->set_texture_buf(std::move(uv));

			ID3D11ShaderResourceView* view = texture->shader_res_view();

			HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
				current_device_, texture_name.c_str(), NULL, NULL, &view, NULL
			);

			if (FAILED(hr))
				assert(false);

			texture_list_.insert(make_pair(texture_name, texture));


		}
	}
}
