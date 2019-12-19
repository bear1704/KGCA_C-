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

	//�»��
	PNode* child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_min.z,
		node->box_blueprint_.aabb_max.z - splited_height
	);
	node->child_list_.push_back(child_node);
	//����
	child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_max.x,
		node->box_blueprint_.aabb_min.z,
		node->box_blueprint_.aabb_max.z - splited_height
	);
	node->child_list_.push_back(child_node);
	//���ϴ�
	child_node = CreateNode(
		node,
		node->box_blueprint_.aabb_min.x,
		node->box_blueprint_.aabb_min.x + splited_width,
		node->box_blueprint_.aabb_max.z - splited_height,
		node->box_blueprint_.aabb_max.z
	);
	node->child_list_.push_back(child_node);
	//���ϴ�
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
	P_BOX* box = static_cast<P_BOX*>(obj); //���Ŀ� �ڽ� �ܿ����� ������Ʈ��..
	if (box->aabb_min.x >= node->box_blueprint_.aabb_min.x &&
		box->aabb_max.x <= node->box_blueprint_.aabb_max.x)
	{
		if (box->aabb_min.z >= node->box_blueprint_.aabb_min.z &&
			box->aabb_max.z <= node->box_blueprint_.aabb_max.z)
		{
			//obj�� �ڽ��� node�� QuadTree Area Box �ȿ� ����
			return true;
		}
	}
	return false; //����
}

//Level-order�� �� �ȿ� object�� �ִ��� Ž��. ����Ʈ���� ��Ʈ->�ڽ�->�ڽ�->�ܸ���� ������ ã�ư���.
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
		if (find_queue.empty()) break; //���̻� �ڽĿ��� ���Ե��� ����(������Ʈ�� ���� ������忡 �̹� ����)

		node = find_queue.front();
		find_queue.pop();

	} while (node);

	return node;
}

void PQuadTree::CheckVisibleObject(PNode* node)
{
	for (int i = 0; i < node->object_list_.size(); i++)
	{
		if (current_camera_->frustum_.CheckCollisionOBB(node->box_blueprint_))
		{
			drawobj_list_.push_back(node->object_list_[i]);
		}
	}
}

void PQuadTree::CheckVisibleNode(PNode* node)
{
	if (node == nullptr) return;
	if (node->is_leaf_)
		drawnode_list_.push_back(node);
	
	int child_size = node->child_list_.size();
	for (int ii = 0; ii < child_size; ii++)
	{
		CheckVisibleNode(node->child_list_[ii]);
	}
}

void PQuadTree::Update(PCamera* camera)
{
	current_camera_ = camera;
}

void PQuadTree::FindAndAddDrawNode(PNode* node)
{
	RELATIVE_POSITION r_pos = current_camera_->frustum_.CheckOBBRelativePos(node->box_blueprint_);

	//back(��尡 �������� �ܺο� ����)
	if (r_pos == RELATIVE_POSITION::BACK) return;

	//�ܸ����鼭, ���� �����ϵ� ��� ���ʿ�(FRONT) �ֵ�, ��·�� ��� �ܸ��̹Ƿ� BACK�� �ƴϸ� �׷����� �Ѵ�.
	if (node->is_leaf_ == true && r_pos != RELATIVE_POSITION::BACK)
	{
		drawnode_list_.push_back(node);
		return;
	}
	/*
	FRONT���, �ܸ� ��常 ��� �׸���.(�θ� ��带 �׸� �ʿ䰡 ����)
	*/
	if (r_pos == RELATIVE_POSITION::FRONT) 
	{
		//drawnode_list_.push_back(node);
		CheckVisibleNode(node);
		return;
	}
	//SPANNING(�������� ��鿡 �����ϰų�, �Ϻθ� ���ʿ� �ִ� ����)�̶��, 
	//�� ���� �׸��� �ʴ´�(������ �ڽĳ��� �������� �׷�����), ��, ������Ʈ�� ���� ©���� �������� �ݵ�� �׷����� �Ѵ�.
	if (r_pos == RELATIVE_POSITION::SPANNING)
	{
		CheckVisibleObject(node);
	}
	//���ȣ��
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

bool PQuadTree::Render(ID3D11DeviceContext* context)
{
	return false;
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

	ComputeBoundingBox(node);

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
			int index = row * map_width_ + col;
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
	node->box_blueprint_.aabb_max.z = v0.z; //�»�� far(z)�� �ٿ���ڽ��� top-left�� �ְ�, ���ϴ� near�� �ٿ���ڽ��� bot-right�� ����
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

void PQuadTreeIndex::CreateIndexBuffer(PNode* node)
{
	// divide(/)�� �迭 �ε����� ���� ���ϱ� ����
	int start_row = node->corner_index_[0] / map_width_;
	int end_row = node->corner_index_[2] / map_width_;
	int start_col = node->corner_index_[0] % map_width_;
	int end_col = node->corner_index_[1] % map_width_;

	/*
	x3 = �ε��� Ʈ���̾ޱ� ���� ���� 3��
	x2 = Ʈ���̾ޱ� 2��(�������� ����Ʈ�� ��� �簢��)
	*/
	node->index_data_.resize((end_row - start_row) * (end_col - start_col) * 2 * 3);

	int index = 0;
	for (int row = start_row; row < end_row; row++)
	{
		for (int col = start_col; col < end_col; col++)
		{
			int next_row = row + 1;
			int next_col = col + 1;
			node->index_data_[index + 0] = row * map_width_ + col;
			node->index_data_[index + 1] = row * map_width_ + next_col;
			node->index_data_[index + 2] = next_row * map_width_ + col;

			node->index_data_[index + 3] = node->index_data_[index + 2];
			node->index_data_[index + 4] = node->index_data_[index + 1];
			node->index_data_[index + 5] = next_row * map_width_ +next_col;

			index += 6;
		}
	}

	node->index_buffer_.Attach(DX::CreateIndexBuffer(map_->device_,
		&node->index_data_.at(0), node->index_data_.size(), sizeof(int), false));
}

bool PQuadTreeIndex::SubTreeDivide(PNode* node)
{
	float splited_width = (node->box_blueprint_.aabb_max.x - node->box_blueprint_.aabb_min.x) / 2;
	float splited_height = (node->box_blueprint_.aabb_max.z - node->box_blueprint_.aabb_min.z) / 2;

	if (max_depth_limit_ <= node->depth_)
	{
		node->is_leaf_ = true;
		CreateIndexBuffer(node);
		return false;
	}

	if (splited_height <= min_devided_size_ || splited_width <= min_devided_size_)
	{
		node->is_leaf_ = true;
		CreateIndexBuffer(node);
		return false;
	}

	int index_center = (node->corner_index_[0] + node->corner_index_[3]) / 2;

	int edge_center_top = (node->corner_index_[0] + node->corner_index_[1]) / 2;
	int edge_center_right = (node->corner_index_[1] + node->corner_index_[3]) / 2;
	int edge_center_bottom = (node->corner_index_[2] + node->corner_index_[3]) / 2;
	int edge_center_left = (node->corner_index_[0] + node->corner_index_[2]) / 2;

	PNode* child_node = CreateNode(
		node,
		node->corner_index_[0],
		edge_center_top,
		edge_center_left,
		index_center
	);
	node->child_list_.push_back(child_node);
	child_node = CreateNode(
		node,
		edge_center_top,
		node->corner_index_[1],
		index_center,
		edge_center_right
	);
	node->child_list_.push_back(child_node);
	child_node = CreateNode(
		node,
		index_center,
		edge_center_right,
		edge_center_bottom,
		node->corner_index_[3]
	);
	node->child_list_.push_back(child_node);
	child_node = CreateNode(
		node,
		edge_center_left,
		index_center,
		node->corner_index_[2],
		edge_center_bottom
	);
	node->child_list_.push_back(child_node);
	return true;
}

bool PQuadTreeIndex::Render(ID3D11DeviceContext* context)
{

	float time = g_fGameTimer;
	map_->constant_data_.color[0] = cosf(time);
	map_->constant_data_.color[1] = sinf(time);
	map_->constant_data_.color[2] = 1 - cosf(time);
	map_->constant_data_.color[3] = 1.0f;
	map_->constant_data_.etc[0] = time;


	context->UpdateSubresource(map_->dx_helper_.constant_buffer_.Get(),
		0, NULL, &map_->constant_data_, 0, 0);
	map_->PreRender();

	int drawnode_size = drawnode_list_.size();
	for (int node = 0; node < drawnode_size; node++)
	{
		PNode* pnode = drawnode_list_[node];
		context->IASetIndexBuffer(pnode->index_buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(pnode->index_data_.size(), 0, 0);
	}

	return true;
}
