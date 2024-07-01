#include <functional>
#include <vector>

using namespace std;

class Solution
{
 public:
  int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime)
  {
    int n = values.size();
    // 建图
    vector<vector<pair<int, int>>> g(n);
    for (auto& e : edges)
    {
      g[e[0]].emplace_back(e[1], e[2]);
      g[e[1]].emplace_back(e[0], e[2]);
    }

    vector<int> visited(n);
    visited[0] = true;
    int ans = 0;

    std::function<void(int, int, int)> dfs = [&](int cur, int time, int value)
    {
      if (cur == 0)
      {
        ans = std::max(ans, value);
      }
      for (auto& [next, dist] : g[cur])
      {
        if (time + dist <= maxTime)
        {
          if (!visited[next])
          {
            visited[next] = true;
            dfs(next, time + dist, value + values[next]);
            visited[next] = false;
          }
          else
          {
            dfs(next, time + dist, value);
          }
        }
      }
    };

    dfs(0, 0, values[0]);

    return ans;
  }
};
