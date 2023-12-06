#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  // 统计每个节点经历的次数
  int dfs(int cur, int parent, int end, vector<int>& count, unordered_map<int, vector<int>>& g)
  {
    if (cur == end)
    {
      // cur 节点可达 end 节点
      count[cur]++;
      return true;
    }
    for (int next : g[cur])
    {
      if (next == parent)
      {
        continue;
      }
      if (dfs(next, cur, end, count, g))
      {
        count[cur]++;
        return true;
      }
    }
    return false;
  }

  struct Info
  {
    // 正常价格
    int normal;
    // 半价
    int half;
  };

  Info dp(int cur, int parent, vector<int>& count, vector<int>& price, unordered_map<int, vector<int>>& g)
  {
    Info base = {count[cur] * price[cur], count[cur] * price[cur] / 2};
    for (int next : g[cur])
    {
      if (next == parent)
      {
        continue;
      }
      Info p1 = dp(next, cur, count, price, g);
      // 当前节点是正常价格，子节点可以取两种情况，在这两种情况下取最小值
      base.normal += std::min(p1.normal, p1.half);
      // 当前节点是半价，子节点必须是正常价格
      base.half += p1.normal;
    }
    return base;
  }

 public:
  int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips)
  {
    unordered_map<int, vector<int>> g;
    for (auto& e : edges)
    {
      // 建图
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    vector<int> count(n);
    for (auto& t : trips)
    {
      // 由于每次旅行互不干扰，因此可以依次处理
      dfs(t[0], -1, t[1], count, g);
    }
    // 因为是无向图，可以从任意节点开始统计，为了方便这里取 0 号节点
    Info info = dp(0, -1, count, price, g);
    return std::min(info.normal, info.half);
  }
};

void test()
{
  Solution s;
  vector<vector<int>> e1 = {{0, 1}, {1, 2}, {1, 3}};
  vector<int> p1 = {2, 2, 10, 6};
  vector<vector<int>> t1 = {{0, 3}, {2, 1}, {2, 3}};
  EXPECT_EQ_INT(23, s.minimumTotalPrice(4, e1, p1, t1));

  vector<vector<int>> e2 = {{0, 1}};
  vector<int> p2 = {2, 2};
  vector<vector<int>> t2 = {{0, 0}};
  EXPECT_EQ_INT(1, s.minimumTotalPrice(4, e2, p2, t2));

  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
