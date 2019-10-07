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

//(�ؽ��ĸŴ���)->�ؽ��ĸ���Ʈ�� �ִ� �ؽ��� ������ �ҷ����� ����..
struct PTexMap
{
	TCHAR texname[kMaxTexname];
	int texmap_id; //unused
};

//�ϳ��� ���׸����� ���긶�׸������ �����ϰ� �ִ�.
struct Material
{
	string material_name;
	int material_id;
	int submaterial_list_size;
	int texmap_size;
	std::vector<PTexMap> tex_list; //unused
	std::vector<Material> sub_material_list;
};

//������Ʈ���� ������ �޽� ���� ����
struct MeshinfoByObject
{
	string meshlist_name;
	string parent_name;
	int material_id;
	int numberof_submesh;
	int trilist_size;
	D3DXMATRIX world_mat;
};

struct PAnimTrack
{
	int				tick;
	D3DXVECTOR3		p;
	D3DXQUATERNION	q;
};

struct MaxScene
{
	int first_frame; // 0
	int last_frame; // 100
	int frame_rate; // 30
	int tick_per_frame; // 160
	int numberof_meshes;
	int numberof_materials;
};


//������Ʈ�� �ʿ��� ���� ����
struct MaxExportInfo
{
	MeshinfoByObject meshinfo;
	vector<Material> material;
	vector<vector<Vertex_PNCT>> vertex_list;
	vector<int> numberof_vertices;
	vector<vector<int>> index_list;
	vector<int> numberof_indicies;

	std::vector<PAnimTrack> animlist_pos;
	std::vector<PAnimTrack> animlist_rot;
	std::vector<PAnimTrack> animlist_scale;
	MaxScene max_scene;

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
	wchar_t wch_t[kCharMaxSize];
public:
	int XmlParse(std::string path, std::vector<std::pair<string,string>>* data_map); //��ȯ�� : �����ͼ�
	int MaxExportParse(OUT_ std::vector<MaxExportInfo>& info_list, std::vector<Material>& material_list , 
		std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device);
	std::vector<std::string> SplitString(std::string str, char delimiter);
	std::vector<std::string> SplitString(std::wstring str, char delimiter);
	inline void ReadNextLineAndSplit(OUT_ std::vector<std::string>& strvec, FILE* infile)
	{
		_fgetts(wch_t, kCharMaxSize, infile);
		std::wstring wstr = wch_t;
		strvec = std::move(SplitString(wstr, ' '));
	}
};

