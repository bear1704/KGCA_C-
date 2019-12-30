#ifdef TEST
#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;


struct Node
{
	int num;
	vector<int> list;
	bool is_using;
	int level;
};

std::queue<int> node_queue;
int max_dist = -999;
int ret_sum = 0;

int solution(int n, vector<vector<int>> edge)
{
	vector<Node> node;
	node.resize(n + 1); //1부터 시작

	for (int j = 1; j < n + 1; j++)
	{
		node[j].num = j;
		node[j].is_using = false;
		node[j].level = 0;
	}

	for (int ii = 0; ii < edge.size(); ii++)
	{
		node[edge[ii][0]].list.push_back(edge[ii][1]);
		node[edge[ii][1]].list.push_back(edge[ii][0]);
	}

	//node 1 세팅
	node[1].is_using = true;
	for (int ii = 0; ii < node[1].list.size(); ii++)
	{
			node[node[1].list[ii]].is_using = true;
			node[node[1].list[ii]].level = node[1].level + 1;
			node_queue.push(node[1].list[ii]);

			if (node[node[1].list[ii]].level > max_dist)
				max_dist = node[node[1].list[ii]].level;

			if (node[node[1].list[ii]].level == max_dist)
			{
				ret_sum++;
			}
	}

	while (node_queue.size() > 0)
	{
		int cur_node = node_queue.front();
		node[cur_node].is_using = true;
		for (int j = 0; j < node[cur_node].list.size(); j++)
		{
			int cur_nodelist_Nth = node[cur_node].list[j];
			if (node[cur_nodelist_Nth].is_using == false)
			{
				node[cur_nodelist_Nth].is_using = true;
				node[cur_nodelist_Nth].level = node[cur_node].level + 1;
				node_queue.push(node[cur_nodelist_Nth].num);


				if (node[cur_nodelist_Nth].level > max_dist)
				{
					ret_sum = 0;
					max_dist = node[cur_nodelist_Nth].level;
				}
				if (node[cur_nodelist_Nth].level == max_dist)
				{
					ret_sum++;
				}

			}
		}

		node_queue.pop();
	}



		
	return ret_sum;
}


int main()
{
	vector<vector<int>> edge;
	edge.push_back({ 3,6 });
	edge.push_back({ 4,3 });
	edge.push_back({ 3,2 });
	edge.push_back({ 1,3 });
	edge.push_back({ 1,2 });
	edge.push_back({ 2,4 });
	edge.push_back({ 5,2 });
	solution(6, edge);

}

#endif