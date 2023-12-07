#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  int dfs(int cur, int parent, vector<vector<std::pair<int, int>>>& g)
  {
    int ans = 0;
    for (auto& next : g[cur])
    {
      if (next.first == parent)
      {
        continue;
      }
      ans += next.second + dfs(next.first, cur, g);
    }
    return ans;
  }

 public:
  int minReorder(int n, vector<vector<int>>& connections)
  {
    vector<vector<std::pair<int, int>>> g(n);
    for (auto& e : connections)
    {
      // 建图，1 标记原方向的边， 0 标记反向边
      g[e[0]].push_back({e[1], 1});
      g[e[1]].push_back({e[0], 0});
    }
    // 以每个点为起点进行搜索的代价会很大，因此考虑从 0 出发去遍历其他点
    // 原来需要统计反向边的数量，现在需要统计原方向边的数量
    return dfs(0, -1, g);
  }
};

void test()
{
  Solution s;
  vector<vector<int>> c1 = {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}};
  EXPECT_EQ_INT(3, s.minReorder(6, c1));
  vector<vector<int>> c2 = {{1, 0}, {1, 2}, {3, 2}, {3, 4}};
  EXPECT_EQ_INT(2, s.minReorder(5, c2));
  EXPECT_SUMMARY;
};

int main()
{
  test();
  return 0;
}
