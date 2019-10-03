#pragma once
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>
#include "PStd.h"
#include "PDxHelper.h"

#define OUT_  
const int kMaxTexname = 256;

using namespace std;

//(텍스쳐매니져)->텍스쳐리스트에 있는 텍스쳐 정보를 불러오기 위한..
struct PTexMap
{
	TCHAR texname[kMaxTexname];
	int texmap_id; //unused
};

//하나의 마테리얼은 서브마테리얼들을 포함하고 있다.
struct Material
{
	string material_name;
	int material_id;
	int submaterial_list_size;
	int texmap_size;
	std::vector<PTexMap> tex_list; //unused
	std::vector<Material> sub_material_list;
};

//오브젝트마다 가지는 메시 정보 모음
struct MeshinfoByObject
{
	string meshlist_name;
	string parent_name;
	int material_id;
	int numberof_submesh;
	int trilist_size;
	D3DXMATRIX world_mat;
};

//오브젝트당 필요한 정보 모음
struct MaxExportInfo
{
	MeshinfoByObject meshinfo;
	vector<Material> material;
	vector<vector<Vertex_PNCT>> vertex_list;
	vector<int> numberof_vertices;
	vector<vector<int>> index_list;
	vector<int> numberof_indicies;

	MaxExportInfo()
	{
		material.reserve(5);
		vertex_list.reserve(5);
		numberof_vertices.reserve(5);
		index_list.reserve(5);
		numberof_indicies.reserve(5);
	}
};



const int kCharMaxSize = 256;

class PParser
{
public:
	PParser();
	~PParser();
private:

public:
	int XmlParse(std::string path, std::vector<std::pair<string,string>>* data_map); //반환값 : 데이터수
	int MaxExportParse(OUT_ std::vector<MaxExportInfo>& info_list, std::vector<Material>& material_list , 
		std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device);
	std::vector<std::string> SplitString(std::string str, char delimiter);
	std::vector<std::string> SplitString(std::wstring str, char delimiter);
	


};

