#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int solution(vector<int> money) {

    vector<int> dp;
    vector<int> dp2;
    dp.resize(money.size() - 1); //1�������� �ʹ� ���(�������� �� ��)
    dp2.resize(money.size()); //2�������� �ʹ� ���(�������� �� �� ����)

    dp[0] = money[0];
    dp[1] = money[0];
    dp2[0] = 0;
    dp2[1] = money[1];

    for (int ii = 2; ii < money.size() - 1; ii++)
    {
        dp[ii] = std::max((money[ii] + dp[ii - 2]), dp[ii - 1]);
    }
    for (int ii = 2; ii < money.size(); ii++)
    {
        dp2[ii] = std::max((money[ii] + dp2[ii - 2]), dp2[ii - 1]);
    }

    return std::max(dp[dp.size() - 1], dp2[dp2.size() - 1]);
}

int main()
{
   //vector<int> m = { 1,2,3,1 };
   vector<int> m = { 10,9,8,7,6};
   //vector<int> m = { 4,7,6,1,1};
  // vector<int> m = { 10,9,8,100,6};
   //vector<int> m = { 1,0,100,50,999,1};

    int ret = solution(m);

}