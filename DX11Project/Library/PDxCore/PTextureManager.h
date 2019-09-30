#pragma once
#include "PTexture.h"
#include "PDxHelper.h"
#include "PParser.h"

class PTextureManager : public PSingleton<PTextureManager>
{
	friend class PSingleton<PTextureManager>;
public:
	~PTextureManager();
private:
	PTextureManager();

	std::map<std::wstring, PTexture*> texture_list_;



public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
	
	void LoadTextureFromScript(multibyte_string filepath, ID3D11Device* current_device);
	PTexture* GetTextureFromMap(std::wstring key);

	DX::PTex_uv ImageCoordinateToTexCoordinate(float x, float y, float image_width, float image_height);

};

