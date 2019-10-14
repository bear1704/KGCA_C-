#pragma once
#include "PExportStd.h"

struct PNCTWI
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;
	float index[4];
	float weight[4];
};

struct PBipedVertex
{
	int numberof_weight;
	//정점의 애니메이션에 영향주는 노드의 인덱스들
	std::vector<BYTE> index_list;
	//각 인덱스별 가중치값
	std::vector<float> weight_list;
};

struct BipedTricomponent
{
	int tri_index;
	PNCTWI v[3];
};


struct PBipedMesh
{
	INode* node;

	TSTR name;
	TSTR parent_name;
	Matrix3 world_tm;
	D3D_MATRIX world_d3d;
	vector<BipedTricomponent> tri_list; //dummy code?
	vector<vector<BipedTricomponent>> buffer_list;
	vector<PBipedVertex> biped_list;
	
	int material_id;
	int numberof_submesh;

	vector<vector<PNCTWI>> vertex_list;
	vector<vector<int>> index_list;

	bool animation_enable[3]; //translate, rotate, scale 애니메이션 존재여부
	std::vector<PAnimTrack> anim_pos;
	std::vector<PAnimTrack> anim_rot;
	std::vector<PAnimTrack> anim_scale;


	PBipedMesh()
	{
		name = L"none";
		parent_name = L"none";
		material_id = -1;
		numberof_submesh = 1;

	}

};

class PSkinExp
{
private:
	PSkinExp();
public:
	virtual ~PSkinExp();

	static PSkinExp& GetInstance()
	{
		static PSkinExp exp;
		return exp;
	}

public:
	FILE*			    file;
	Interface*		    interface_max_;
	std::wstring		filename_;
	INode*				rootnode_;
	PScene				scene_;

	std::vector<INode*> biped_list_;
	std::vector<INode*> object_list_;
	std::vector<PBipedMesh> mesh_list_;

	std::vector<Mtl*> material_list_;
	std::vector<PMtl> pmtl_list_;

	Interval interval_;

public:
	void Set(const TCHAR* name, Interface* interface_max);
	bool Export();
	void PreProcess(INode* node);
	void AddObject(INode* node);
	void GetMesh(INode* node, OUT_  PBipedMesh& pmesh);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue timeval, bool& deleteit);
	bool IsTmNegativeParity(Matrix3 tm);
	Point3 GetVertexNormal(Mesh* mesh, int iFace, RVertex* rVertex);
	void GetTexture(PMtl& pmtl, Mtl* mtl);
	void CopyPoint3(Point3& dest, Point3& src);
	void GetMaterial(INode* node);
	void AddMaterial(INode* node);
	int FindMaterialIndex(INode* node);
	Mtl* FindMaterial(INode* node);
	TCHAR* FixupName(MSTR name);
	bool SwitchAllNodeToMesh();

	bool EqualPoint2(Point2 p1, Point2 p2);
	bool EqualPoint3(Point3 p1, Point3 p2);
	bool EqualPoint4(Point4 pq, Point4 p2);
	int IsEqualVertexAndVertexList(PNCTWI& vertex, std::vector<PNCTWI>& vertex_list);
	void CopyMatrix3(OUT_ D3D_MATRIX& d3d_world, Matrix3& matWorld);
	void SetUniqueBuffer(PBipedMesh& mesh);

	void GetAnimation(INode* node, PBipedMesh& mesh);
	void ExportAnimation(PBipedMesh& mesh);

	TCHAR* SaveFileDialog(TCHAR* extension, TCHAR* title);

public:
	void SetBipedInfo(INode* node, PBipedMesh& bmesh);
	Modifier* FindModifier(INode* node, Class_ID classid);
	void ExportPhysiqueData(INode* node, Modifier* modi, PBipedMesh& mesh);
	void ExportSkinData(INode* node, Modifier* modi, PBipedMesh& mesh);
	int GetFindIndex(INode* node);

};


