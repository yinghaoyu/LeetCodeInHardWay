#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/alien-dictionary/
// @sa Problem_0269_alienOrder.cc
class Solution
{
 public:
  string alienOrder(vector<string>& words)
  {
    int n = words.size();
    unordered_map<char, int> indegree;
    for (int i = 0; i < n; i++)
    {
      for (auto& c : words[i])
      {
        // 初始时所有节点入度为0
        indegree[c] = 0;
      }
    }
    unordered_map<char, unordered_set<char>> graph;
    for (int i = 0; i < n - 1; i++)
    {
      string cur = words[i];
      string next = words[i + 1];
      int len = std::min(cur.length(), next.length());
      int j = 0;
      for (; j < len; j++)
      {
        if (cur[j] != next[j])
        {
          if (!graph.count(cur[j]))
          {
            graph.emplace(cur[j], unordered_set<char>());
          }
          // 这个 if 确保 cur[j] -> next[j]是第一次加入的
          // 否则会让next[j]的入度额外增加，导致后续结果不对
          if (!graph[cur[j]].count(next[j]))
          {
            graph[cur[j]].emplace(next[j]);
            indegree[next[j]]++;
          }
          break;
        }
      }
      if (j < cur.length() && j == next.length())
      {
        // next 变成了 cur 的子串，这明显不符合题意
        return "";
      }
    }
    string ans;
    queue<char> q;
    for (auto& [key, _] : indegree)
    {
      if (indegree[key] == 0)
      {
        q.push(key);
      }
    }
    while (!q.empty())
    {
      char cur = q.front();
      q.pop();
      ans.push_back(cur);
      for (char next : graph[cur])
      {
        if (--indegree[next] == 0)
        {
          q.push(next);
        }
      }
    }
    return ans.size() == indegree.size() ? ans : "";
  }
};
