
#ifdef TEST
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define MIN_(a,b) (a <= b) ? (a) : (b)

//남은 부분이 A연속인가
bool CheckASequence(int start, int end, const string& str)
{
    for (int ii = start; ii <= end; ii++)
    {
        if (str[ii] != 'A')
            return false;
    }
    return true;
}

int Traverse(string& name, bool isReverse)
{
    if (CheckASequence(0, name.size() - 1, name))
        return 0;

    int sum = 0;
    int cur = 0;
    if (isReverse == true)
    {
        sum = 1;
        cur = name.size() - 1;
    }

    if (isReverse == false)
    {
        while (cur < name.size())
        {
            bool isAseq = CheckASequence(cur + 1, name.size() - 1, name);
            if (isAseq == false)
            {
                sum += MIN_(name[cur] - 'A', 'Z' - name[cur] + 1);
                cur++; sum++;
            }
            else
            {
                sum += MIN_(name[cur] - 'A', 'Z' - name[cur] + 1);
                return sum;
            }
        }
    }
    else
    {
        sum += MIN_(name[0] - 'A', 'Z' - name[0] + 1);

        while (cur > 0)
        {
            bool isAseq = CheckASequence(0, cur, name);
            if (isAseq == false)
            {
                sum += MIN_(name[cur] - 'A', 'Z' - name[cur] + 1);
                cur--; sum++;
            }
            else
            {
                sum += MIN_(name[cur] - 'A', 'Z' - name[cur] + 1);
                return sum;
            }
        }
    }


    return sum;
}





int solution(string name) {
    int answer = 0;
    return answer;
}

int main()
{
    string str = "JAN"; //9 123456789
    int a = Traverse(str, false);

}

#endif