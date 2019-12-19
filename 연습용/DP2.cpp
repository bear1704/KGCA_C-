#ifdef TEST

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#define MAX_(a,b) ((a) > (b)) ? (a) : (b)


vector<vector<int>> S;
vector<int> Max;
int tmp_max = -9999999;


int solution(vector<vector<int>> triangle) {

    S.resize(triangle.size());
    for (int ii = 0; ii < triangle.size(); ii++)
    {
        S[ii].resize(triangle[ii].size());
    }

    Max.resize(triangle.size());

    S[0][0] = triangle[0][0];
    Max[0] = S[0][0];

    for (int ii = 1; ii < triangle.size(); ii++)
    {
        for (int j = 0; j < triangle[ii].size(); j++)
        {
            if (j == 0)
                S[ii][j] = S[ii - 1][j] + triangle[ii][j];
            else if (j == triangle[ii].size() - 1)
                S[ii][j] = S[ii - 1][j - 1] + triangle[ii][j];
            else
                S[ii][j] = MAX_((S[ii - 1][j - 1] + triangle[ii][j]), (S[ii - 1][j] + triangle[ii][j]));

            if (tmp_max < S[ii][j])
                tmp_max = S[ii][j];
        }

        Max[ii] = tmp_max;
        tmp_max = -9999999;
    }

    return Max[triangle.size() - 1];
}


int main()
{
    vector<vector<int>> tri;
    tri.push_back({ 7 });
    tri.push_back({ 3,8 });
    tri.push_back({ 8,1,0 });
    tri.push_back({ 2,7,4,4 });
    tri.push_back({ 4,5,2,6,5 });

    int a = solution(tri);


}

#endif