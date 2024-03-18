#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 拓扑排序
  vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges)
  {
    if (n == 1)
    {
      // 特殊处理
      return {0};
    }
    vector<vector<int>> g(n);
    vector<int> degree(n);
    for (auto& edge : edges)
    {
      g[edge[0]].emplace_back(edge[1]);
      g[edge[1]].emplace_back(edge[0]);
      degree[edge[0]]++;
      degree[edge[1]]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
      // 因为把树当作无向图，所以从度为 1 的开始
      if (degree[i] == 1)
      {
        q.push(i);
      }
    }
    // 剩余节点数
    int remains = n;
    // 剩余节点数 > 2，这两个节点任取其一都满足条件
    while (remains > 2)
    {
      int size = q.size();
      remains -= size;
      for (int i = 0; i < size; i++)
      {
        int cur = q.front();
        q.pop();
        for (int next : g[cur])
        {
          if (--degree[next] == 1)
          {
            q.push(next);
          }
        }
      }
    }
    vector<int> ans;
    while (!q.empty())
    {
      ans.emplace_back(q.front());
      q.pop();
    }
    return ans;
  }

  // TODO: 通过 bfs 或 dfs 解决此问题
};
