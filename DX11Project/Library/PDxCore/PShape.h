#pragma once
#include "PModel.h"
#include "PSpriteManager.h"
#include "PParser.h"

class PPlaneObject : public PModel
{
public:
	PPlaneObject();
	~PPlaneObject();

private:
	PSprite sprite_;

public:
	//bool DXInit(ID3D11Device* device, ID3D11DeviceContext* context) override;
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring tex_name = L"", std::wstring sprite_name = L"");
	bool Frame() override;
	bool Render() override;
public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;

};

class PBoxObject : public PModel
{
public:
	PBoxObject();
	~PBoxObject();
	
private:
	PSprite sprite_;

public:
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring tex_name = L"", std::wstring sprite_name = L"");

	bool Frame() override;
	bool Render() override;

public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;

};

struct PGeoMesh  //오브젝트별 geomesh
{
	std::vector<std::vector<Vertex_PNCT>> vertices_list_;
	std::vector<std::vector<int>> indices_list_;
	std::vector<DX::PDxHelper> helper_list_;
	MaxExportInfo info;
};

class PImportObject : public PModel
{
public:
	PImportObject();
	~PImportObject();

private:
	std::vector<PGeoMesh> object_list_;
public:
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring object_path = L"");

	virtual HRESULT CreateVertexBuffer() override;
	virtual HRESULT CreateIndexBuffer() override;
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual bool PostRender() override;
	bool Render() override;

};