#include <vector>
#include <algorithm>	

struct TreeNode {
	std::vector<TreeNode*> children;
};

int longest; //���±��� ã�� ���� �� ��-�� ����� ���� ����

int height(TreeNode* root)
{
	std::vector<int> heights; 
	
	for (int i = 0; i < root->children.size(); i++) //�ڽ� ��带 ���� ��ŭ �ݺ��Ѵ�.
	{
		heights.push_back(height(root->children[i])); //������ ��Ʈ(�ڽ�)�� ���� �ڽĳ���� �ִ� ���̸� �����´�.
	}

	if (heights.empty()) //�ڽ��� ���� ���(�ܸ������ ���) 0�� �����Ѵ�.
		return 0;

	std::sort(heights.begin(), heights.end()); //�ڽ� ������ ���̰� ��, ���� ���̰� ���� ����Ʈ���� ���̰��� �˰� �����Ƿ� �����Ѵ�.
	
	if (heights.size() >= 2)
		longest = std::max(longest, 1 + heights[heights.size() - 1] + 1 + heights[heights.size() - 2]);  
		//���� ū �� ���� ����Ʈ���� ������ �ִ�ġ + 1�� ��η� �ϴ� ���̰���, ���� ���� �� ���̰�(longest)�� ���Ͽ� �� ���� �����Ѵ�.

	return heights.back() + 1; //�ڽ��� ���� ����Ʈ���� ���� �ִ밪 + 1(�ڽű����� ���̰� ���ԵǾ�� �ϹǷ�)

}

int solve(TreeNode* root)
{
	longest = 0;
	int h = height(root);
	return std::max(longest, h);
}