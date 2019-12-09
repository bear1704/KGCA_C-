#include <string>
#include <vector>

using namespace std;
int** already_come;

int cnt = 0;

void DFS(int j, int n, vector<vector<int>>& computers)
{

    for (int k = 0; k < n; k++)
    {
        if (j == k)
            continue;
        if (computers[j][k] == 1 && already_come[j][k] != 1)
        {
            already_come[j][k] = 1;
            already_come[k][j] = 1;
            DFS(k, n, computers);
        }
    }
}

int solution(int n, vector<vector<int>> computers)
{

    already_come = new int* [n]();

    for (int i = 0; i < n; i++)
    {
        already_come[i] = new int[n];
        
    }


    for (int ii = 0; ii < n; ii++)
    {
        bool is_isolated = true;
        bool is_count = false;
        for (int j = 0; j < n; j++)
        {
            if (ii == j)
                continue;
            if (computers[ii][j] == 1)
            {
                is_isolated = false;
                if (already_come[ii][j] != 1)
                {
                    is_count = true;
                    already_come[ii][j] = 1;
                    already_come[j][ii] = 1;
                    DFS(j, n, computers);
                }
            }
            
        }
        if (is_count == true)
            cnt++;

        if (is_isolated == true)
            cnt++;
    }

    return cnt;

}

int main()
{
    /*vector<vector<int>> c = { 
    {1,0,0,0,1},
    {0,1,0,0,1},
    {0,0,1,1,0},
    {0,0,1,1,0}, 
    {1,1,0,0,1} };*/

    //vector<vector<int>> c = { {1,1,0},{1,1,0},{0,0,1} };
    //vector<vector<int>> c = { {1,1,0},{1,1,1},{0,1,1} };
    //vector<vector<int>> c = { {1} };
    vector<vector<int>> c = { {1,0,0,1},{0,1,1,1},{0,1,1,0},{1,1,0,1} };

    // vector<vector<int>> c = {
    //{1,0,0,1,0},
    //{0,1,1,0,1},
    //{0,1,1,0,0},
    //{1,0,0,1,0},
    //{0,1,0,0,1} };

    int ret = solution(4, c);

    return 0;
}