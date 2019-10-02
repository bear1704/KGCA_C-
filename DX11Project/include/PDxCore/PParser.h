#pragma once
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>
#include "PStd.h"
#include "PDxHelper.h"

#define OUT_  

using namespace std;

struct MaxExportInfo
{
	struct Submaterial
	{
		string submaterial_name;
		int texmap_size;
		int texmap_id;
		string texmap_name;
	};


	//FIRSTLINE
	string obj_name;
	int numberof_obj;
	//MATERIAL INFO
	string material_name;
	int submaterial_list_size;


	//OBJECT INFO
	string meshlist_name;
	string parent_name;
	int material_id;
	int bufferlist_size;
	int trilist_size;

	D3DXMATRIX world_mat;

	//VECTOR
	vector<Submaterial> submaterial;
	
	vector<vector<Vertex_PNCT>> vertex_list;
	vector<int> numberof_vertices;
	vector<vector<int>> index_list;
	vector<int> numberof_indicies;

	MaxExportInfo()
	{
		obj_name = "";
		numberof_obj = 0;
		material_name = "";
		submaterial_list_size = 0;
		submaterial.reserve(5);
		vertex_list.reserve(5);
		numberof_vertices.reserve(5);
		index_list.reserve(5);
		numberof_indicies.reserve(5);
	}
};



const int kParsingLineMaxSize = 256;

class PParser
{
public:
	PParser();
	~PParser();
private:
	

public:
	int XmlParse(std::string path, std::vector<std::pair<string,string>>* data_map); //반환값 : 데이터수
	int MaxExportParse(OUT_ MaxExportInfo& info, std::wstring path);
	std::vector<std::string> SplitString(std::string str, char delimiter);
	std::vector<std::string> SplitString(std::wstring str, char delimiter);
	


};

