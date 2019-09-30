#pragma once
#include <string>
#include <map>
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>

#define OUT_  

using namespace std;

struct PNCT
{
	float p[3];
	float n[3];
	float c[4];
	float t[2];
};

struct MaxExportInfo
{
	struct Submaterial
	{
		string submaterial_name;
		int texmap_size;
		int texmap_id;
		string texmap_name;
	};

	struct MATRIX4 {
		float        _11, _12, _13, _14;
		float        _21, _22, _23, _24;
		float        _31, _32, _33, _34;
		float        _41, _42, _43, _44;
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

	MATRIX4 world_mat;

	//VECTOR
	vector<Submaterial> submaterial;
	
	vector<vector<PNCT>> vertex_list;
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
	int MaxExportParse(OUT_ MaxExportInfo& info, std::string path);
	std::vector<std::string> SplitString(std::string str, char delimiter);
	std::string Utf16ToString(wchar_t* wchar, int max_size, std::wifstream* in);


};

