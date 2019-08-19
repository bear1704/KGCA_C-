#pragma once
#include "PTexture.h"

class PTextureManager : public PSingleton<PTextureManager>
{
	friend class PSingleton<PTextureManager>;
public:
	~PTextureManager();
private:
	PTextureManager();

	std::map<std::wstring, PTexture*> texture_list_;

	ID3D11Device* current_device_;

public:
	void LoadTextureFromScript(multibyte_string filepath);
	PTexture* GetTextureFromMap(std::wstring key);


};

