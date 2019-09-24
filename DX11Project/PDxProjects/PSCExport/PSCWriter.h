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

public:
	void Set(const TCHAR* name, Interface* interface_max);
	bool Export();
	void PreProcess(INode* node);
	void AddObject(INode* node);
	void GetMesh(INode* node);
	TriObject* GetTriObjectFromNode(INode* node, TimeValue timeval, bool& deleteit);

};

