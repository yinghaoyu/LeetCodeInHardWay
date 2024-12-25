#include <cstdint>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV1Cm4y1g77W/

class Solution
{
 private:
  class cmp
  {
   public:
    bool operator()(std::tuple<int, int, int>& lhs, std::tuple<int, int, int>& rhs)
    {
      return get<2>(lhs) > get<2>(rhs);
    }
  };

 public:
  // 电动车总电量，cnt
  int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge)
  {
    int n = charge.size();
    vector<vector<std::pair<int, int>>> graph(n);
    for (auto& path : paths)
    {
      graph[path[0]].push_back({path[1], path[2]});
      graph[path[1]].push_back({path[0], path[2]});
    }
    // n : 0 ~ n-1，不代表图上的点
    // (点，到达这个点的电量)图上的点！
    vector<vector<int>> distance(n, vector<int>(cnt + 1, INT32_MAX));
    distance[start][0] = 0;
    vector<vector<bool>> visited(n, vector<bool>(cnt + 1));
    // 0 : 当前点
    // 1 : 来到当前点的电量
    // 2 : 花费时间
    priority_queue<std::tuple<int, int, int>, vector<std::tuple<int, int, int>>, cmp> heap;
    heap.push({start, 0, 0});
    while (!heap.empty())
    {
      auto [cur, power, cost] = heap.top();
      heap.pop();
      if (cur == end)
      {
        return cost;
      }
      visited[cur][power] = true;
      if (power < cnt)
      {
        // 充一格电
        // cur, power + 1
        if (!visited[cur][power + 1] && cost + charge[cur] < distance[cur][power + 1])
        {
          distance[cur][power + 1] = cost + charge[cur];
          heap.push({cur, power + 1, cost + charge[cur]});
        }
      }
      for (auto& [nextCity, d] : graph[cur])
      {
        // 不充电去别的城市
        int restPower = power - d;
        int nextCost = cost + d;
        if (restPower >= 0 && !visited[nextCity][restPower] &&
            nextCost < distance[nextCity][restPower])
        {
          distance[nextCity][restPower] = nextCost;
          heap.push({nextCity, restPower, nextCost});
        }
      }
    }
    return -1;
  }
};
