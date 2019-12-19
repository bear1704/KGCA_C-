#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool IsChangeable(string a, string b, int n)
{
	int diff_count = 0;

	for (int ii = 0; ii < n; ii++)
	{
		if (a[ii] != b[ii])
			diff_count++;

		if (diff_count > 1)
			return false;
	}

	//같은 단어 제거
	if (diff_count == 1)
		return true;

	return false;
}

std::vector<string> start_queue;
std::vector<string> start_origin;
std::vector<string> end_queue;
std::vector<int> ret_queue;
//std::vector<std::vector<string>> debug_ret_queue;
string g_target;

int conversion_count = 0;

bool DFS(string start, string word, int word_size)
{
	conversion_count++;

	end_queue.push_back(word);
	auto iter = std::find(start_queue.begin(), start_queue.end(), word);
	start_queue.erase(iter);

	if (word == g_target)
	{
		auto ret_iter = std::find(ret_queue.begin(), ret_queue.end(), conversion_count);

		if (ret_iter == ret_queue.end())
			ret_queue.push_back(conversion_count);

		//debug_ret_queue.push_back(end_queue);
		start_queue.push_back(*(end_queue.end() - 1));
		end_queue.erase(end_queue.end() - 1);

		conversion_count--;

		return true;
	}

	for (int ii = 0; ii < start_queue.size(); ii++)
	{

		if (IsChangeable(word, start_queue[ii], word_size))
		{
			if (DFS(word, start_queue[ii], word_size))
				break;
		}
	}


	start_queue.push_back(*(end_queue.end() - 1));
	end_queue.erase(end_queue.end() - 1);
	conversion_count--;

	return false;

}

int solution(string begin, string target, vector<string> words) {

	g_target = target;
	start_origin.resize(words.size());
	start_queue.resize(words.size());
	std::copy(words.begin(), words.end(), start_origin.begin());
	std::copy(words.begin(), words.end(), start_queue.begin());

	for (int ii = 0; ii < words.size(); ii++)
	{
		if (IsChangeable(begin, words[ii], words[0].size()))
			DFS(begin, words[ii], words[0].size());

		conversion_count = 0;
	}

	if (ret_queue.size() == 0)
		return 0;

	std::sort(ret_queue.begin(), ret_queue.end());

	return ret_queue[0];
}