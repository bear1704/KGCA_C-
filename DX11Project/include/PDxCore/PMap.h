#pragma once
#include "PModel.h"

struct PMapDesc
{
	int vertex_rows;
	int vertex_cols;
	float cell_disatnce;
	std::wstring texture_name;
	std::wstring vs_path = L"";
	std::string vs_func = "";
	std::wstring ps_path = L"";
	std::string ps_func = "";
};


class PMap : public PModel
{
private:
	int vertex_rows_;
	int vertex_cols_;
	int cell_rows_;
	int cell_cols_;
	int numberof_faces_;
	int numberof_vertices_;
	float cell_distance_;

public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual bool Load(PMapDesc& md);

public:
	PMap();
	virtual ~PMap();


};

