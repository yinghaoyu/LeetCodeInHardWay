#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string alienOrder(vector<string> &words)
  {
    if (words.size() == 0)
    {
      return "";
    }
    int N = words.size();
    unordered_map<char, int> indegree;
    for (int i = 0; i < N; i++)
    {
      for (char c : words[i])
      {
        // 初始化每个字符入度为0
        indegree[c] = 0;
      }
    }
    unordered_map<char, unordered_set<char>> graph;
    for (int i = 0; i < N - 1; i++)
    {
      string cur = words[i];
      string next = words[i + 1];
      int len = std::min(cur.length(), next.length());
      int j = 0;
      // 构建有向图
      for (; j < len; j++)
      {
        // 根据多级排序规则
        // 第一个不同的字符才需要处理
        if (cur[j] != next[j])
        {
          if (!graph.count(cur[j]))
          {
            graph.emplace(cur[j], unordered_set<char>{});
          }
          if (!graph.at(cur[j]).count(next[j]))
          {
            graph.at(cur[j]).emplace(next[j]);
            indegree.at(next[j])++;
          }
          break;
        }
      }
      if (j < cur.length() && j == next.length())
      {
        // next是cur的子串，那么应该next排在前面，所以序列非法
        return "";
      }
    }
    string ans;
    queue<char> q;
    for (auto &[key, _] : indegree)
    {
      if (indegree.at(key) == 0)
      {
        q.push(key);
      }
    }
    while (!q.empty())
    {
      char cur = q.front();
      q.pop();
      ans.push_back(cur);
      if (graph.count(cur))
      {
        for (char next : graph.at(cur))
        {
          if (--indegree[next] == 0)
          {
            q.push(next);
          }
        }
      }
    }
    return ans.length() == indegree.size() ? ans : "";
  }
};

void testAlienOrder()
{
  Solution s;
  vector<string> w1 = {"wrt", "wrf", "er", "ett", "rftt"};
  vector<string> w2 = {"z", "x"};
  vector<string> w3 = {"z", "x", "z"};
  EXPECT_TRUE("wertf" == s.alienOrder(w1));
  EXPECT_TRUE("zx" == s.alienOrder(w2));
  EXPECT_TRUE("" == s.alienOrder(w3));
  EXPECT_SUMMARY;
}

int main()
{
  testAlienOrder();
  return 0;
}
