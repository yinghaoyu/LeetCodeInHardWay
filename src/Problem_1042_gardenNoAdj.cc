#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> gardenNoAdj(int n, vector<vector<int>> &paths)
  {
            // 生成邻接表
    vector<vector<int>> adj(n);
    for (auto &path : paths)
    {
      adj[path[0] - 1].emplace_back(path[1] - 1);
      adj[path[1] - 1].emplace_back(path[0] - 1);
    }
    // 初始颜色都是 0，表示没有颜色
    vector<int> ans(n);
    // 遍历花园
    for (int i = 0; i < n; i++)
    {
      vector<bool> colored(5, false);
      //遍历花园的邻接点，记录已经被邻接点占用的颜色
      for (auto &vertex : adj[i])
      {
        // 花园 vertex 的颜色被标记为已占用
        colored[ans[vertex]] = true;
      }
      for (int j = 1; j <= 4; j++)
      {
        // 从 colors 中未占用的颜色里，挑一种给花园 i 使用
        if (colored[j] == 0)
        {
          ans[i] = j;
          break;
        }
      }
    }
    return ans;
  }
};

void testGardenNoAdj()
{
  Solution s;
  vector<vector<int>> p1 = {{1, 2}, {2, 3}, {3, 1}};
  vector<vector<int>> p2 = {{1, 2}, {3, 4}};
  vector<int> o1 = {1, 2, 3};
  vector<int> o2 = {1, 2, 1, 2};
  EXPECT_TRUE(o1 == s.gardenNoAdj(3, p1));
  EXPECT_TRUE(o2 == s.gardenNoAdj(4, p2));
  EXPECT_SUMMARY;
}

int main()
{
  testGardenNoAdj();
  return 0;
}
