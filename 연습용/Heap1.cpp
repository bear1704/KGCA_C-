#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;


int solution(vector<vector<int>> jobs) {
    int answer = 0;

    int cur_time = 0;
    int sum_time = 0;

    //pair의 경우 first비교, 같으면 second 비교
    //first : 걸리는 시간     second : 들어오는 시점
    std::queue<pair<int, int>> wating_queue;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> time_q;

    for (int ii = 0; ii < jobs.size(); ii++)
    {
        pair<int, int> p = make_pair(jobs[ii][1], jobs[ii][0]);
        time_q.push(p);
    }

    while (time_q.empty() == false)
    {
        while (time_q.empty() == false)
        {
            pair<int, int> p = time_q.top();
            if (p.second > cur_time)
            {
                wating_queue.push(p);
                time_q.pop();
            }
            else
            {
                sum_time += (cur_time - p.second) + p.first;
                cur_time += p.first;
                time_q.pop();

                int prev_size = wating_queue.size();

                //하나 들어갔으므로 관계 재생성
               // for (int ii = 0; ii < prev_size; ii++)
               // {
               //     time_q.push(wating_queue.front());
               //     wating_queue.pop();
               // }
            }

        }
        if (time_q.empty() == true && wating_queue.size() > 0) //유휴 상태
        {
            int min = 501;
            pair<int, int> minnode = make_pair(-999, -999);

            int prev_size = wating_queue.size();

            for (int ii = 0; ii < prev_size; ii++)
            {
                if (wating_queue.front().second < min)
                {
                    min = wating_queue.front().second;
                    if (minnode.first != -999)
                        wating_queue.push(minnode);

                    minnode = make_pair(wating_queue.front().first, wating_queue.front().second);
                    wating_queue.pop();
                }
                else
                {
                    //최소가 아닐경우 큐의 맨 뒤로 이동
                    wating_queue.push(wating_queue.front());
                    wating_queue.pop();
                }
            }

            time_q.push(minnode);
            cur_time = minnode.second;

            pair<int, int> p = time_q.top();
            //MIN NOde 작업(유휴상태일때)
            sum_time += (cur_time - p.second) + p.first;
            cur_time += p.first;
            time_q.pop();
        }

        while (wating_queue.empty() == false)
        {
            time_q.push(wating_queue.front());
            wating_queue.pop();
        }

    }

    answer = sum_time / jobs.size();
    answer = std::floor(answer);
    return answer;
}

int main()
{
    //vector<vector<int>> jobs = { {0,3}, {1,9}, {2,6} };
    //vector<vector<int>> jobs = { {0,3}, {10,1}, {4,5}, {11,40} };
   // vector<vector<int>> jobs = { {10,1}, {4,5}, {11,40} };
    //vector<vector<int>> jobs = { {0,9},{0,4},{0,5},{0,7},{0,3} };
    vector<vector<int>> jobs = { {0,5} ,{1,2},{5,5} };
    int ret = solution(jobs);
    return 0;

}