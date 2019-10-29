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
	node->box_blueprint_.obb_extents[0] = (node->box_blueprint_.aabb_max.y - node->box_blueprint_.aabb_min.y) / 2;
	node->box_blueprint_.obb_extents[0] = (node->box_blueprint_.aabb_max.z - node->box_blueprint_.aabb_min.z) / 2;

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

	//back(��尡 �������� �ܺο� ����)
	if (r_pos == RELATIVE_POSITION::BACK) return;

	//�ܸ����鼭, ���� �����ϵ� ��� ���ʿ�(FRONT) �ֵ�, ��·�� ��� �ܸ��̹Ƿ� BACK�� �ƴϸ� �׷����� �Ѵ�.
	if (node->is_leaf_ == true && r_pos != RELATIVE_POSITION::BACK)
	{
		drawnode_list_.push_back(node);
		return;
	}
	//FRONT���, �ܸ��̵� �θ�� ��Ʈ�� �� ������ �׷����� �Ѵ�
	if (r_pos == RELATIVE_POSITION::FRONT) 
	{
		drawnode_list_.push_back(node);
		return;
	}
	//SPANNING(�������� ��鿡 �����ϰų�, �Ϻθ� ���ʿ� �ִ� ����)�̶��, 
	//�� ���� �׸��� �ʴ´�(������ �ڽĳ��� �������� �׷�����), ��, ������Ʈ�� ���� ©���� �������� �ݵ�� �׷����� �Ѵ�.
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
