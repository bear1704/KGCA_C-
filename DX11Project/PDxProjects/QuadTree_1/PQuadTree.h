#pragma once
#include "PNode.h"
#include "PNormHeightMap.h"
#include "PFreeCamera.h"
#include "PFrustum.h"
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
	PCamera* current_camera_;
public:
	bool	Build(float width, float height, int maxdepth, float minsize);
	PNode*	CreateNode(PNode* parent_node, float xmin, float xmax, float zmin, float zmax);
	bool	BuildTree(PNode* node);
	bool	SubTreeDivide(PNode* node);
	void	AddObject(P_BaseObj* p_obj);
	bool	IsObjInQdTreeSquare(PNode* node, P_BaseObj* obj);
	PNode*	FindNode(PNode* node, P_BaseObj* obj);
	void	IsVisibleObject(PNode* node);
	void	Update(PCamera* camera);
	void	FindAndAddDrawNode(PNode* node);

public:
	bool Frame();
	bool Release();


};

class PQuadTreeIndex : public PQuadTree
{
public:
	int map_width_;
	int map_height_;
	PMap* map_;
public:
	bool	Build(PMap* map, int maxdepth, float minsize);
	PNode* CreateNode(PNode* parent_node, int idx_top_l, int idx_top_r, int idx_bot_l, int idx_bot_r);
	D3DXVECTOR2 GetHeightFromNode(int idx_top_l, int idx_top_r, int idx_bot_l, int idx_bot_r);
	void ComputeBoundingBox(PNode* node);



};