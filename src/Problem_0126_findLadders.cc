#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution
{
 private:
  list<string> path;
  unordered_set<string> dict;
  vector<vector<string>> ans;
  unordered_set<string> curLevel;
  unordered_set<string> nextLevel;
  unordered_map<string, vector<string>> g;

  // begin -> end，一层层 bfs 去建图
  // 找到 begin 到 end 的路径，则返回 true
  bool bfs(string& begin, string& end)
  {
    bool flag = false;
    curLevel.emplace(begin);
    while (!curLevel.empty())
    {
      for (auto& s : curLevel)
      {
        dict.erase(s);
      }
      for (auto& s : curLevel)
      {
        string tmp = s;
        // 每个位置，字符 a-z 都试一遍
        for (int i = 0; i < tmp.size(); ++i)
        {
          char old = tmp[i];
          for (char ch = 'a'; ch <= 'z'; ++ch)
          {
            if (ch != old)
            {
              tmp[i] = ch;
              if (dict.count(tmp))
              {
                if (tmp == end)
                {
                  // 找到 begin 到 end 的路径了
                  flag = true;
                }
                // 建反图
                g[tmp].emplace_back(s);
                nextLevel.emplace(tmp);
              }
            }
          }
          tmp[i] = old;
        }
      }

      if (flag)
      {
        // 找到了路径
        return true;
      }
      else
      {
        curLevel.swap(nextLevel);
        nextLevel.clear();
      }
    }
    return false;
  }

  // dfs 利用 bfs 形成的反图去生成路径
  void dfs(string& word, string& target)
  {
    path.emplace_front(word);
    if (word == target)
    {
      ans.emplace_back(vector<string>(path.begin(), path.end()));
    }

    for (auto& next : g[word])
    {
      dfs(next, target);
    }
    // 回溯
    path.pop_front();
  }

 public:
  vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
  {
    dict = unordered_set<string>(wordList.begin(), wordList.end());
    if (!dict.count(endWord))
    {
      return ans;
    }

    if (bfs(beginWord, endWord))
    {
      dfs(endWord, beginWord);
    }
    return ans;
  }
};
