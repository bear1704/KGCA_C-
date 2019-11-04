#include "PQuadTree.h"

bool PQuadTree::Build(float width, float height, int maxdepth, float minsize)
{
	rootnode_ = CreateNode(nullptr, -width / 2, width / 2, -height / 2, height / 2);
	max_depth_limit_ = maxdepth;
	min_devided_size_ = minsize;
	return BuildTree(rootnode_);
}


PNode* PQuadTree::CreateNode(PNode* parent_node, float xmin, float xmax, float zmin, float zmax)
{
	PNode* node = new PNode;
	node->child_list_.reserve(kNumberOfDivide);
	node->is_leaf_ = false;

	node->box_blueprint_.aabb_max.x = xmax;
	node->box_blueprint_.aabb_max.y = 0.0f;
	node->box_blueprint_.aabb_max.z = zmax;
	
	node->box_blueprint_.aabb_min.x = xmin;
	node->box_blueprint_.aabb_min.y = 0.0f;
	node->box_blueprint_.aabb_min.z = zmin;

	node->box_blueprint_.center = (node->box_blueprint_.aabb_max + node->box_blueprint_.aabb_min) / 2;

	node->box_blueprint_.obb_axis[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	node->box_blueprint_.obb_axis[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	node->box_blueprint_.obb_axis[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	node->box_blueprint_.obb_extents[0] = (node->box_blueprint_.aabb_max.x - node->box_blueprint_.aabb_min.x) / 2;
	node->box_blueprint_.obb_extents[1] = (node->box_blueprint_.aabb_max.y - node->box_blueprint_.aabb_min.y) / 2;
	node->box_blueprint_.obb_extents[2] = (node->box_blueprint_.aabb_max.z - node->box_blueprint_.aabb_min.z) / 2;

	node->depth_ = 0;
	if (parent_node != nullptr)
	{
		node->depth_ = parent_node->depth_ + 1;
	}

	return node;

}


bool PQuadTree::BuildTree(PNode* node)
{
	if (SubTreeDivide(node))
	{
		for (int i = 0; i < node->child_list_.size(); i++)
		{
			BuildTree(node->child_list_[i]);
		}
	}
	return true;
}

bool PQuadTree::SubTreeDivide(PNode* node)
{
	float splited_width = (node->box_blueprint_.aabb_max.x - node->box_blueprint_.aabb_min.x) / 2;
	float splited_height = (node->box_blueprint_.aabb_max.z - node->box_blueprint_.aabb_min.z) / 2;
	
	if (max_depth_limit_ <= node->depth_)
	{
		node->is_leaf_ = true;
		return false;
	}

	if (splited_height <= min_devided_size_ || splited_width <= min_devided_size_)
	{
		node->is_leaf_ = true;
		return false;
	}
	//좌상단
	PNode* child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_min.z,
		node->box_blueprint_.aabb_max.z - splited_height
	);
	node->child_list_.push_back(child_node);
	//우상단
	child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_max.x,
		node->box_blueprint_.aabb_min.z,
		node->box_blueprint_.aabb_max.z - splited_height
	);
	node->child_list_.push_back(child_node);
	//좌하단
	child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_max.z - splited_height,
		node->box_blueprint_.aabb_max.z
	);
	node->child_list_.push_back(child_node);
	//우하단
	child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_max.x,
		node->box_blueprint_.aabb_max.z - splited_height,
		node->box_blueprint_.aabb_max.z
	);
	node->child_list_.push_back(child_node);

	return true;
}

void PQuadTree::AddObject(P_BaseObj* p_obj)
{
	if (IsObjInQdTreeSquare(rootnode_, p_obj))
	{
		PNode* node = FindNode(rootnode_, p_obj);
		if (node)
		{
			node->object_list_.push_back(p_obj);
		}
	}
}

//CheckRect
bool PQuadTree::IsObjInQdTreeSquare(PNode* node, P_BaseObj* obj)
{
	P_BOX* box = static_cast<P_BOX*>(obj); //이후에 박스 외에에도 오브젝트로..
	if (box->aabb_min.x >= node->box_blueprint_.aabb_min.x &&
		box->aabb_max.x <= node->box_blueprint_.aabb_max.x)
	{
		if (box->aabb_min.z >= node->box_blueprint_.aabb_min.z &&
			box->aabb_max.z <= node->box_blueprint_.aabb_max.z)
		{
			//obj의 박스가 node의 QuadTree Area Box 안에 있음
			return true;
		}
	}
	return false; //없음
}

//Level-order로 이 안에 object가 있는지 탐색. 쿼드트리의 루트->자식->자식->단말노드 순으로 찾아간다.
PNode* PQuadTree::FindNode(PNode* node, P_BaseObj* obj)
{
	if (!node)
		assert(false);

	std::queue <PNode*> find_queue;
	do
	{
		for (int i = 0; i < node->child_list_.size(); i++)
		{
			if (IsObjInQdTreeSquare(node->child_list_[i], obj))
			{
				find_queue.push(node->child_list_[i]);
			}
		}
		if (find_queue.empty()) break; //더이상 자식에서 포함되지 않음(오브젝트를 가진 리프노드에 이미 도달)

		node = find_queue.front();
		find_queue.pop();

	} while (node);

	return node;
}

void PQuadTree::IsVisibleObject(PNode* node)
{
	for (int i = 0; i < node->object_list_.size(); i++)
	{
		if (current_camera_->frustum_.CheckCollisionOBB(node->box_blueprint_))
		{
			drawobj_list_.push_back(node->object_list_[i]);
		}
	}
}

void PQuadTree::Update(PCamera* camera)
{
	current_camera_ = camera;
}

void PQuadTree::FindAndAddDrawNode(PNode* node)
{
	RELATIVE_POSITION r_pos = current_camera_->frustum_.CheckOBBRelativePos(node->box_blueprint_);

	//back(노드가 프러스텀 외부에 존재)
	if (r_pos == RELATIVE_POSITION::BACK) return;

	//단말노드면서, 평면과 교차하든 평면 안쪽에(FRONT) 있든, 어쨌든 얘는 단말이므로 BACK만 아니면 그려져야 한다.
	if (node->is_leaf_ == true && r_pos != RELATIVE_POSITION::BACK)
	{
		drawnode_list_.push_back(node);
		return;
	}
	//FRONT라면, 단말이든 부모든 루트든 다 무조건 그려져야 한다
	if (r_pos == RELATIVE_POSITION::FRONT) 
	{
		drawnode_list_.push_back(node);
		return;
	}
	//SPANNING(프러스텀 평면에 교차하거나, 일부만 안쪽에 있는 상태)이라면, 
	//그 노드는 그리지 않는다(어차피 자식노드로 내려가서 그려진다), 단, 오브젝트는 반이 짤려서 나오더라도 반드시 그려져야 한다.
	if (r_pos == RELATIVE_POSITION::SPANNING)
	{
		IsVisibleObject(node);
	}
	for (int i = 0; i < node->child_list_.size(); i++)
	{
		FindAndAddDrawNode(node->child_list_[i]);
	}

}



bool PQuadTree::Frame()
{
	drawobj_list_.clear();
	drawnode_list_.clear();

	FindAndAddDrawNode(rootnode_);
	return true;
}

bool PQuadTree::Release()
{
	delete rootnode_;
	return true;
}



bool PQuadTreeIndex::Build(PMap* map, int maxdepth, float minsize)
{
	map_width_ = map->vertex_cols();
	map_height_ = map->vertex_rows();
	map_ = map;

	rootnode_ = CreateNode(nullptr, 0,
		map_width_ - 1,
		map_width_ * (map_height_ - 1),
		(map_width_ * map_height_) - 1);

	max_depth_limit_ = maxdepth;
	min_devided_size_ = minsize;
	return BuildTree(rootnode_);
}



PNode* PQuadTreeIndex::CreateNode(PNode* parent_node, int idx_top_l, int idx_top_r, int idx_bot_l, int idx_bot_r)
{
	PNode* node = new PNode;
	node->child_list_.reserve(kNumberOfDivide);
	node->is_leaf_ = false;

	node->corner_index_.at(0) = idx_top_l;
	node->corner_index_.at(1) = idx_top_r;
	node->corner_index_.at(2) = idx_bot_l;
	node->corner_index_.at(3) = idx_bot_r;

	node->depth_ = 0;
	if (parent_node != nullptr)
	{
		node->depth_ = parent_node->depth_ + 1;
	}

	return node;
}

D3DXVECTOR2 PQuadTreeIndex::GetHeightFromNode(int idx_top_l, int idx_top_r, int idx_bot_l, int idx_bot_r)
{

	float min = 99999.9f;
	float max = -99999.9f;

	int start_row = idx_top_l / map_width_;
	int end_row = idx_bot_l / map_height_;
	int start_col = idx_top_l % map_width_;
	int end_col = idx_top_r % map_width_;

	for (int row = start_row; row < end_row; row++)
	{
		for (int col = start_col; col < end_col; col++)
		{
			int index = row * map_width_ * col;
			if (map_->vertex_list_[index].pos.y < min)
			{
				min = map_->vertex_list_[index].pos.y;
			}
			if (map_->vertex_list_[index].pos.y > max)
			{
				max = map_->vertex_list_[index].pos.y;
			}
		}
	}

	return D3DXVECTOR2(min, max);
}

void PQuadTreeIndex::ComputeBoundingBox(PNode* node)
{
	D3DXVECTOR2 minmax_height = GetHeightFromNode(
		node->corner_index_.at(0),
		node->corner_index_.at(1),
		node->corner_index_.at(2),
		node->corner_index_.at(3));

	int idx_top_l = node->corner_index_.at(0);
	int idx_bot_r = node->corner_index_.at(3);

	D3DXVECTOR3 v0 = map_->vertex_list_[idx_top_l].pos;
	D3DXVECTOR3 v1 = map_->vertex_list_[idx_bot_r].pos;

	node->box_blueprint_.aabb_max.x = v1.x;
	node->box_blueprint_.aabb_max.y = minmax_height.y;
	node->box_blueprint_.aabb_max.z = v0.z; //좌상단 far(z)에 바운딩박스의 top-left가 있고, 우하단 near에 바운딩박스의 bot-right가 있음
	node->box_blueprint_.aabb_min.x = v0.x;
	node->box_blueprint_.aabb_min.y = minmax_height.x;
	node->box_blueprint_.aabb_min.z = v1.z;
	node->box_blueprint_.center = (node->box_blueprint_.aabb_max + node->box_blueprint_.aabb_min) / 2;

	node->box_blueprint_.obb_axis[0] = D3DXVECTOR3(1, 0, 0);
	node->box_blueprint_.obb_axis[1] = D3DXVECTOR3(0, 1, 0);
	node->box_blueprint_.obb_axis[2] = D3DXVECTOR3(0, 0, 1);

	node->box_blueprint_.obb_extents[0] = (node->box_blueprint_.aabb_max.x - node->box_blueprint_.aabb_min.x) / 2;
	node->box_blueprint_.obb_extents[1] = (node->box_blueprint_.aabb_max.y - node->box_blueprint_.aabb_min.y) / 2;
	node->box_blueprint_.obb_extents[2] = (node->box_blueprint_.aabb_max.z - node->box_blueprint_.aabb_min.z) / 2;

}
