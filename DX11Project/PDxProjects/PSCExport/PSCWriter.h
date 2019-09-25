#pragma once
#include <string>
#include <vector>

struct PNCT
{
	Point3 p;
	Point3 n;
	Point4 c;
	Point2 t;

};

struct TriList
{
	PNCT  v[3];
};

struct PMtrl
{
	int map_id;
	TSTR name;
};

class PSCWriter
{
public:
	PSCWriter();
	~PSCWriter();

protected:
	Interface*			interface_max_;
	std::wstring		filename_;
	INode*				rootnode_;
	std::vector<INode*> object_list_;
	std::vector<TriList> tri_list_;
	std::vector<PMtrl> tex_list_;

public:
	void Set(const TCHAR* name, Interface* interface_max);
	bool Export();
	void PreProcess(INode* node);
	void AddObject(INode* node);
	void GetMesh(INode* node);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue timeval, bool& deleteit);
	bool IsTmNegativeParity(Matrix3 tm);
	Point3 GetVertexNormal(Mesh* mesh, int iFace, RVertex* rVertex);
	void GetMaterial(INode* node);
	void GetTexture(Mtl* mtl);
	void CopyPoint3(Point3& dest, Point3& src);
	


};

