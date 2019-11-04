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

enum class FILE_EXTENSION_TYPE
{
	KGC,
	SKM,
	MAT,
	OBJECT,
	ERROR_OCCUR,
};

struct Vertex_PNCTW8I8
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 color;
	D3DXVECTOR2 uv;
	D3DXVECTOR4 i0;
	D3DXVECTOR4 w0;
	D3DXVECTOR4 i1;
	D3DXVECTOR4 w1;

};

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
struct MeshinfoByObject //TMeshHeader
{
	string meshlist_name;
	string parent_name;
	int material_id;
	int numberof_submesh;
	int numberof_face;
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

	MaxScene()
	{
		first_frame = 0;
		last_frame = 0;
		frame_rate = 0;
		tick_per_frame = 0;
		numberof_meshes = 0;
		numberof_materials = 0;

	}
};

struct PBox
{
	D3DXVECTOR3 center;
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
	D3DXVECTOR3 axis[3];
};

//������Ʈ�� �ʿ��� ���� ����
struct MaxExportInfoInterface
{
	vector<vector<int>> index_list;
	MeshinfoByObject meshinfo;
	vector<Material> material;
	vector<int> numberof_vertices;
	vector<int> numberof_indicies;

	std::vector<PAnimTrack> animlist_pos;
	std::vector<PAnimTrack> animlist_rot;
	std::vector<PAnimTrack> animlist_scale;


	MaxExportInfoInterface()
	{
		material.reserve(5);
		numberof_vertices.reserve(5);
		index_list.reserve(5);
		numberof_indicies.reserve(5);
	}
};

//������Ʈ�� �ʿ��� ���� ����
struct MaxExportInfo : public MaxExportInfoInterface
{
public:
	vector<vector<Vertex_PNCT>> vertex_list;
	PBox bounding_box; // mat animation only
};

struct MaxExportSkinInfo : public MaxExportInfoInterface
{
	vector<vector<Vertex_PNCTW8I8>> vertex_list;
	std::vector<D3DXMATRIX> bone_list;
};




const int kCharMaxSize = 256;
const int kDoubledLineMaxSize = 512;

using StringPair = std::pair<string, string> ;

class PParser
{
	//extension type
	//0 = kgc
	//1 = skm
	//2 = mat

public:
	PParser();
	~PParser();
private:
	wchar_t wch_t[kDoubledLineMaxSize];
public:
	int XmlParse(std::string path, std::vector<std::pair<string,string>>* data_map); //��ȯ�� : �����ͼ�
	int CharacterSheetParse(std::wstring filepath, OUT_ std::vector<StringPair>* data_map);
	int MaxExportParse(OUT_ std::vector<MaxExportInfo>& info_list, std::vector<Material>& material_list, MaxScene& scene, 
		std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device, FILE_EXTENSION_TYPE type);
	int MaxExportParse(OUT_ std::vector<MaxExportSkinInfo>& info_list, std::vector<Material>& material_list, MaxScene& scene,
		std::wstring exportfile_path, std::wstring texfile_path, ID3D11Device* device, FILE_EXTENSION_TYPE type);
	std::vector<std::string> SplitString(std::string str, char delimiter);
	std::vector<std::string> SplitString(std::wstring str, char delimiter);
	inline void ReadNextLineAndSplit(OUT_ std::vector<std::string>& strvec, FILE* infile)
	{
		_fgetts(wch_t, kCharMaxSize, infile);
		std::wstring wstr = wch_t;
		strvec = std::move(SplitString(wstr, ' '));
	}
};

