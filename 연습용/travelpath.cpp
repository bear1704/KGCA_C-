//#define TEST
#ifdef TEST
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>


using namespace std;
//총 공항이 몇개인가
int return_size = 0;
//현재 방문한 에어포트 리스트 
std::vector<std::string> airport_list;
//결과값
std::vector<std::vector<std::string>> final_list;
//티켓소모여부
std::vector<pair<string,string>> new_ticket;
std::vector<pair<string,string>> use_ticket;


struct Node
{
    std::string name;
    std::vector<Node*> next;

    Node()
    {
    }
    Node(std::string name_)
    {
        name = name_;
    }
};

void DFS(Node* cur_node, int return_size_)
{
    int child_size = cur_node->next.size();
    airport_list.push_back(cur_node->name);


    for (int ii = 0; ii < child_size; ii++)
    {
        bool ok_using_ticket = false;
        for (auto iter = new_ticket.begin() ; iter != new_ticket.end() ; )
        {
            if (iter->first == cur_node->name && iter->second == cur_node->next[ii]->name)
            {
                use_ticket.push_back(make_pair(cur_node->name, cur_node->next[ii]->name));
                new_ticket.erase(iter);
                ok_using_ticket = true;
                break;
            }
            iter++;
        }

        if(ok_using_ticket)
            DFS(cur_node->next[ii], return_size_);
    }

    if (use_ticket.size() == return_size)
    {
           final_list.push_back(airport_list);
    }

    if (airport_list.size() != 0)
        airport_list.erase(std::end(airport_list) - 1);

    if (use_ticket.size() != 0)
    {
        new_ticket.push_back(use_ticket[use_ticket.size() - 1]);
        use_ticket.erase(std::end(use_ticket) - 1);
    }

}


vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;

    std::map<std::string, Node*> node_list;
    std::vector<std::string> node_name_list;
    Node* node = nullptr;
    Node* node_child = nullptr;


    for (int ii = 0; ii < tickets.size(); ii++)
    {
        auto iter       =   node_list.find(tickets[ii][0]);
        auto iter_child =   node_list.find(tickets[ii][1]);

        //새로운 노드
        if (iter == node_list.end())
        {
            node = new Node(tickets[ii][0]);
            node_list.insert(make_pair(tickets[ii][0], node));
            node_name_list.push_back(tickets[ii][0]);
        }
        //있는 노드를 불러온다
        else
            node = (Node*)iter->second;

        if (iter_child == node_list.end())
        {
            node_child = new Node(tickets[ii][1]);
            node_list.insert(make_pair(tickets[ii][1], node_child));
            node_name_list.push_back(tickets[ii][1]);
        }
        else
            node_child = (Node*)iter_child->second;

        node->next.push_back(node_child);  //그래프의 cur->next 관계 결속
        new_ticket.push_back(make_pair(tickets[ii][0], tickets[ii][1]));
    }

    return_size = tickets.size();

    for(int j = 0 ; j < node_name_list.size(); j++)
    {
        if(node_name_list[j] == "ICN")
            DFS((Node*)node_list.find(node_name_list[j])->second, return_size);
    }
    
    std::sort(final_list.begin(), final_list.end());


    return final_list[0];
}


int main()
{
    //std::vector<std::vector<string>> tickets = {{"ICN", "SFO"},{"ICN", "ATL"},{"SFO", "ATL"},{"ATL", "ICN"},{"ATL","SFO"}};
    std::vector<std::vector<string>> tickets = { {"ICN", "JFK"}, {"HND", "IAD"}, { "JFK", "HND" } };
    solution(tickets);


    return 0;
}


#endif