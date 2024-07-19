#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // dijkstra
  vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear)
  {
    // 建图
    vector<vector<std::pair<int, int>>> g(n);
    for (auto& e : edges)
    {
      int from = e[0];
      int to = e[1];
      int d = e[2];
      g[from].emplace_back(to, d);
      g[to].emplace_back(from, d);
    }
    // 根据距离从小到大排序
    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, greater<std::pair<int, int>>>
        q;
    q.emplace(0, 0);
    // ans[i] 含义为 0 到 i 的最短距离
    vector<int> ans(n, -1);
    // 0 点到自己为 0
    ans[0] = 0;
    while (!q.empty())
    {
      auto [cost, cur] = q.top();
      q.pop();
      if (cost != ans[cur])
      {
        // 思考: 如何理解这个条件?
        continue;
      }
      for (auto& [next, d] : g[cur])
      {
        if (cost + d < disappear[next] && (ans[next] == -1 || cost + d < ans[next]))
        {
          q.emplace(cost + d, next);
          ans[next] = cost + d;
        }
      }
    }
    return ans;
  }
};
