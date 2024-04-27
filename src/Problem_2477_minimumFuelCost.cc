#include <functional>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 树型dp
class Solution
{
 public:
  long long minimumFuelCost(vector<vector<int>>& roads, int seats)
  {
    unordered_map<int, vector<int>> g;
    for (auto& e : roads)
    {
      // 建图
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    long long ans = 0;
    function<int(int, int)> dfs = [&](int cur, int parent)
    {
      // 每个节点只有一个人
      int after = 1;
      for (int next : g[cur])
      {
        if (next == parent)
        {
          // 禁止遍历父节点
          continue;
        }
        // 所有子节点到达当前节点的人数
        int before = dfs(next, cur);
        // 统计当前节点所需消耗的油量
        ans += (before + seats - 1) / seats;
        after += before;
      }
      return after;
    };
    // 从 0 节点开始向下遍历
    dfs(0, -1);
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> r1 = {{0, 1}, {0, 2}, {0, 3}};
  vector<vector<int>> r2 = {{3, 1}, {3, 2}, {1, 0}, {0, 4}, {0, 5}, {4, 6}};
  vector<vector<int>> r3;
  EXPECT_EQ_INT(3, s.minimumFuelCost(r1, 5));
  EXPECT_EQ_INT(7, s.minimumFuelCost(r2, 2));
  EXPECT_EQ_INT(0, s.minimumFuelCost(r3, 1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
