#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// TODO: figure it out.
// @sa https://www.bilibili.com/video/BV1Dw411w7P5/
class Solution
{
 public:
  int minStickers(vector<string>& stickers, string target)
  {
    vector<vector<string>> graph(26);
    unordered_set<string> visited;
    for (auto& str : stickers)
    {
      // 贴纸排序不影响结果
      std::sort(str.begin(), str.end());
      // 建图，当前贴纸能搞定多少字符
      for (int i = 0; i < str.length(); i++)
      {
        // 过滤重复
        if (i == 0 || str[i] != str[i - 1])
        {
          // graph[c] 表示能搞定字符 c 的贴纸
          graph[str[i] - 'a'].push_back(str);
        }
      }
    }
    // 排序不影响结果
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
        // 检查哪些贴纸可以搞定首字符
        for (auto& s : graph[cur[0] - 'a'])
        {
          // cur = "aabccff"
          // s = "accccfkk"
          // next = "abf"
          // 用 s 贴纸搞定 cur 里的字符，还剩余的字符next
          string next = getNext(cur, s);
          if (next.empty())
          {
            // 目标达成
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

  // t = "aabccff"
  // s = "accccfkk"
  // next = "abf"
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
