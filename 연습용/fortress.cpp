#include <vector>
#include <algorithm>	

struct TreeNode {
	std::vector<TreeNode*> children;
};

int longest; //여태까지 찾은 가장 긴 잎-잎 노드의 길이 저장

int height(TreeNode* root)
{
	std::vector<int> heights; 
	
	for (int i = 0; i < root->children.size(); i++) //자식 노드를 가진 만큼 반복한다.
	{
		heights.push_back(height(root->children[i])); //현재의 루트(자신)이 가진 자식노드의 최대 높이를 가져온다.
	}

	if (heights.empty()) //자식이 없을 경우(단말노드일 경우) 0을 리턴한다.
		return 0;

	std::sort(heights.begin(), heights.end()); //자식 노드들의 높이값 중, 가장 높이가 높은 서브트리의 높이값을 알고 싶으므로 정렬한다.
	
	if (heights.size() >= 2)
		longest = std::max(longest, 1 + heights[heights.size() - 1] + 1 + heights[heights.size() - 2]);  
		//가장 큰 두 개의 서브트리의 높이의 최대치 + 1을 경로로 하는 길이값과, 현재 가장 긴 길이값(longest)를 비교하여 긴 것을 적용한다.

	return heights.back() + 1; //자신이 가진 서브트리의 깊이 최대값 + 1(자신까지의 길이가 포함되어야 하므로)

}

int solve(TreeNode* root)
{
	longest = 0;
	int h = height(root);
	return std::max(longest, h);
}