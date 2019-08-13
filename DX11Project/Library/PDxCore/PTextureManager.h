#pragma once
#include "PStd.h"
#include "PTexture.h"

class PTextureManager : public PSingleton<PTextureManager>
{
public:
	~PTextureManager();
private:
	PTextureManager();
	friend class PSingleton<PTextureManager>;

	std::map<std::wstring, PTexture*> texture_list_;

	ID3D11Device* current_device_;

public:
	void LoadTextureFromScript(multibyte_string filepath);



};

