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
	PGeoMesh* parent_geomesh;

	D3DXMATRIX mat_inverse_world;  //GetNodeTm Inv
	D3DXMATRIX mat_calculation;
	D3DXMATRIX mat_world_self; 
	D3DXMATRIX mat_pos;
	D3DXMATRIX mat_rot;
	D3DXMATRIX mat_scale;
	D3DXVECTOR3 pos_track;
	D3DXVECTOR3 scale_track;
	D3DXQUATERNION rot_track;

};



class PImportObject : public PModel
{
public:
	PImportObject();
	~PImportObject();

public:
	std::vector<PGeoMesh> object_list_;
	std::vector<Material> material_list_;
	float elapsed_time_;
	MaxScene scene_;

public:
	bool Init(ID3D11Device* device, ID3D11DeviceContext* context,
		std::wstring vs_file_path, std::string vs_func_name, std::wstring ps_file_path, std::string ps_func_name,
		std::wstring object_path = L"", std::wstring texcomp_path = L"");
	virtual bool Frame() override;
	virtual HRESULT CreateVertexBuffer() override;
	virtual HRESULT CreateIndexBuffer() override;
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual bool PostRender() override;

public:
	bool GetAnimationTrack(const float elapsed_time, const std::vector<PAnimTrack>& tracklist,
		OUT_ PAnimTrack& start_track, OUT_ PAnimTrack& end_track);
	void Interpolate(PGeoMesh& mesh, D3DXMATRIX& mat_parent, float elapsed_time);

};