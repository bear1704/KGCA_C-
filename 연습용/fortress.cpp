#include <vector>
#include <algorithm>	

struct TreeNode {
	std::vector<TreeNode*> children;
};

int longest; //여태까지 찾은 가장 긴 잎-잎 노드의 길이 저장

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