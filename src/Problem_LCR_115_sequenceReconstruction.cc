#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/sequence-reconstruction/
// @sa Problem_0444_sequenceReconstruction.cc
class Solution
{
 public:
  bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences)
  {
    int n = nums.size();
    vector<int> indegree(n + 1);
    vector<unordered_set<int>> graph(n + 1);
    for (auto& s : sequences)
    {
      // 为每个序列内相邻的数建立有向图
      for (int i = 0; i < s.size() - 1; i++)
      {
        int cur = s[i];
        int next = s[i + 1];
        if (!graph[cur].count(next))
        {
          graph[cur].emplace(next);
          indegree[next]++;
        }
      }
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
      if (indegree[i] == 0)
      {
        q.emplace(i);
      }
    }
    while (!q.empty())
    {
      if (q.size() > 1)
      {
        // 如果队列里的元素 > 1，说明最后的拓扑结构不唯一
        return false;
      }
      int cur = q.front();
      q.pop();
      for (int next : graph[cur])
      {
        if (--indegree[next] == 0)
        {
          q.emplace(next);
        }
      }
    }
    return true;
  }
};
