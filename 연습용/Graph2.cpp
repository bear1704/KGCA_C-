#ifdef TEST

#include <string>
#include <vector>

using namespace std;


int visit[101][101] = { 0, };
int ret[101] = { 0, };
vector<vector<int>> ans_node;

void TraceLoseLine(vector<vector<int>>& lose_node ,int origin, int child)
{
	if (visit[origin][child] == 0)
	{
		visit[origin][child] = 1;
		ans_node[origin].push_back(child);

		int tmp_size = lose_node[child].size();
		for (int ii = 0; ii < tmp_size; ii++)
		{
			TraceLoseLine(lose_node, origin, lose_node[child][ii]);
		}
		
	}

}

int solution(int n, vector<vector<int>> results) {

	//답
	int ret_count = 0;

	//vector[node][노드에 해당하는 리스트 노드 인덱스]
	vector<vector<int>> lose_node; 
	lose_node.resize(n + 1);

	ans_node.resize(n + 1);

	vector<int> node_win_count;
	node_win_count.resize(n + 1);

	for (int k = 0 ; k < node_win_count.size(); k++)
	{
		node_win_count[k] = 0;

	}


	//패배선 긋기, 승리카운트 올리기
	for (int ii = 0; ii < results.size(); ii++)
	{
		lose_node[results[ii][0]].push_back(results[ii][1]);
		node_win_count[results[ii][0]]++;
	}

	//순회하며 나머지 패배선 긋기
	for (int j = 1; j < lose_node.size(); j++)
	{
		int tmp_size = lose_node[j].size();

		for (int k = 0; k < tmp_size; k++)
			TraceLoseLine(lose_node, j, lose_node[j][k]);
		
	}
	for (int j = 1; j < ans_node.size(); j++)
	{
		for (int k = 0; k < ans_node[j].size(); k++)
		{
			ret[ans_node[j][k]] += 1;
		}

	}
	
	for (int k = 1; k < n + 1; k++)
	{
		if (node_win_count[k] + ret[k] == n - 1)
			ret_count++;
	}

	return ret_count;
}


int main()
{
	vector<vector<int>> results = { {4,3}, {4,2}, {3,2}, {1,2}, {2,5} };
	solution(5, results);

}

#endif TEST