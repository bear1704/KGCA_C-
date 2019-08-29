#pragma once
#include "PModel.h"
#include "PSpriteManager.h"

class PPlaneObject : public PModel
{

public:
	PPlaneObject();
	~PPlaneObject();

private:
	PSprite sprite_; 

public:
	//bool DXInit(ID3D11Device* device, ID3D11DeviceContext* context) override;
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context, std::wstring tex_name,std::wstring sprite_name, 
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name);
	bool Frame();
	bool Render() override;

public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	



};

