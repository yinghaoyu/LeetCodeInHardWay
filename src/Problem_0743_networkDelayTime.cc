#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Prim 和 Diskstra 算法的区别：
// Prim更新的是未标记集合到已标记集合之间的距离
// Dijkstra更新的是源点到未标记集合之间的距离
// Prim是计算最小生成树的算法，比如为N个村庄修路，怎么修花销最少
// Dijkstra是计算最短路径的算法，比如从a村庄走到其他任意村庄的距离

// Dijkstra算法模版
class Solution
{
 private:
  class cmp
  {
   public:
    bool operator()(std::pair<int, int>& lhs, std::pair<int, int>& rhs)
    {
      return lhs.second > rhs.second;
    }
  };

 public:
  // 动态建图+普通堆的实现
  int networkDelayTime(vector<vector<int>>& times, int n, int k)
  {
    vector<vector<std::pair<int, int>>> graph(n + 1);
    for (auto& e : times)
    {
      graph[e[0]].push_back({e[1], e[2]});
    }
    vector<bool> visited(n + 1);
    static const int MAX = 1e6;
    vector<int> distance(n + 1, MAX);
    // 0 : 当前节点
    // 1 : 源点到当前点距离，按从小到大排序
    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, cmp> heap;
    distance[k] = 0;
    heap.push({k, 0});
    while (!heap.empty())
    {
      auto [u, _] = heap.top();
      heap.pop();
      visited[u] = true;
      for (auto& [v, w] : graph[u])
      {
        if (!visited[v] && distance[u] + w < distance[v])
        {
          distance[v] = distance[u] + w;
          heap.push({v, distance[v]});
        }
      }
    }
    int ans = INT32_MIN;
    for (int i = 1; i <= n; i++)
    {
      if (distance[i] == MAX)
      {
        return -1;
      }
      ans = std::max(ans, distance[i]);
    }
    return ans;
  }
};
