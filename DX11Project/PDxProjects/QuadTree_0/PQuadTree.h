#pragma once
#include "PNode.h"
#include <queue>

const int kNumberOfDivide = 4;

class PQuadTree
{
public:
	PNode* rootnode_;
	int		max_depth_limit_;
	float	min_devided_size_;
	vector<PNode*> drawnode_list_;
	vector<P_BaseObj*> drawobj_list_;
public:
	bool Build(float width, float height, int maxdepth, float minsize);
	PNode* CreateNode(PNode* parent_node, float xmin, float xmax, float zmin, float zmax);
	bool BuildTree(PNode* node);
	bool SubTreeDivide(PNode* node);
	void AddObject(P_BaseObj* p_obj);
	bool IsObjInQdTreeSquare(PNode* node, P_BaseObj* obj);
	PNode* FindNode(PNode* node, P_BaseObj* obj);

}
	


};

