#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  int minStickers(vector<string>& stickers, string target)
  {
    vector<vector<string>> graph(26);
    unordered_set<string> visited;
    for (auto& str : stickers)
    {
      std::sort(str.begin(), str.end());
      for (int i = 0; i < str.length(); i++)
      {
        if (i == 0 || str[i] != str[i - 1])
        {
          graph[str[i] - 'a'].push_back(str);
        }
      }
    }
    std::sort(target.begin(), target.end());
    visited.emplace(target);
    queue<string> que;
    que.push(target);
    int level = 1;
    // 使用队列的形式是整层弹出
    while (!que.empty())
    {
      int size = que.size();
      for (int i = 0; i < size; i++)
      {
        string cur = que.front();
        que.pop();
        for (auto& s : graph[cur[0] - 'a'])
        {
          string next = getNext(cur, s);
          if (next.empty())
          {
            return level;
          }
          else if (!visited.count(next))
          {
            visited.emplace(next);
            que.push(next);
          }
        }
      }
      level++;
    }
    return -1;
  }

  string getNext(string& t, string& s)
  {
    string ans;
    for (int i = 0, j = 0; i < t.length();)
    {
      if (j == s.length())
      {
        ans.push_back(t[i++]);
      }
      else
      {
        if (t[i] < s[j])
        {
          ans.push_back(t[i++]);
        }
        else if (t[i] > s[j])
        {
          j++;
        }
        else
        {
          i++;
          j++;
        }
      }
    }
    return ans;
  }
};
