#include <vector>
#include <algorithm>	

struct TreeNode {
	std::vector<TreeNode*> children;
};

int longest; //���±��� ã�� ���� �� ��-�� ����� ���� ����

int height(TreeNode* root)
{
	std::vector<int> heights;
	
	for (int i = 0; i < root->children.size(); i++)
	{
		heights.push_back(height(root->children[i]));
	}

	if (heights.empty())
		return 0;

	std::sort(heights.begin(), heights.end());


}