#include <cstdint>
#include <queue>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int reachableNodes(vector<vector<int>> &edges, int maxMoves, int n)
  {
    // 建图
    unordered_map<int, unordered_map<int, int>> g;
    for (auto &e : edges)
    {
      g[e[0]][e[1]] = g[e[1]][e[0]] = e[2] + 1;
    }
    //堆优化，小根堆
    auto cmp = [](const pair<int, int> &l, const pair<int, int> &r) { return l.second > r.second; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(cmp);
    // 节点0到其他点的最短距离
    vector<int> d(n, INT32_MAX);
    // 自己到自己距离为0
    d[0] = 0;
    // dijkstra
    que.push({0, 0});
    while (!que.empty())
    {
      // 每次出堆的都是距离0点最短的可达点
      auto cur = que.top().first;
      que.pop();
      // 如果距离大于maxMoves则停止
      if (d[cur] >= maxMoves)
      {
        break;
      }
      for (auto &[next, w] : g[cur])
      {
        if (d[next] > d[cur] + w)
        {
          d[next] = d[cur] + w;
          que.push({next, d[next]});
        }
      }
    }
    // 开始做本题
    int res = 0;
    // 先计算出原始图中所有可达节点数量
    for (int i = 0; i < n; i++)
    {
      if (d[i] <= maxMoves)
      {
        res++;
      }
    }
    // 考虑细分图
    for (auto &e : edges)
    {
      // 让每条边的两个节点沿这条边往对方节点走，看看有多少个细分节点是可达的
      int a = e[0], b = e[1], cnta = 0, cntb = 0;
      if (d[a] < maxMoves)
      {
        // 计算它往外还能多走几个细分节点
        cnta = std::min(e[2], maxMoves - d[a]);
      }
      if (d[b] < maxMoves)
      {
        cntb = std::min(e[2], maxMoves - d[b]);
      }
      // 如果 cnta 和 cntb 有重叠，说明这条边上的细分节点都是可达的
      res += std::min(e[2], cnta + cntb);
    }
    return res;
  }
};

void testReachableNodes()
{
  Solution s;
  vector<vector<int>> e1 = {{0, 1, 10}, {0, 2, 1}, {1, 2, 2}};
  vector<vector<int>> e2 = {{0, 1, 4}, {1, 2, 6}, {0, 2, 8}, {1, 3, 1}};
  vector<vector<int>> e3 = {{1, 2, 4}, {1, 4, 5}, {1, 3, 1}, {2, 3, 4}};
  EXPECT_EQ_INT(13, s.reachableNodes(e1, 6, 3));
  EXPECT_EQ_INT(23, s.reachableNodes(e2, 10, 4));
  EXPECT_EQ_INT(1, s.reachableNodes(e3, 17, 5));
  EXPECT_SUMMARY;
}

int main()
{
  testReachableNodes();
  return 0;
}
