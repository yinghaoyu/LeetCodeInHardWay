#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minCost(vector<vector<int>> &costs)
  {
    int n = costs.size();
    // dp[i][j] 表示粉刷 0...j 房子，且第 i 号房子刷 j 颜色时，最小的花费成本
    vector<vector<int>> dp(n, vector<int>(3));
    for (int j = 0; j < 3; j++)
    {
      dp[0][j] = costs[0][j];
    }
    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        // TODO: 空间优化
        dp[i][j] = std::min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]) + costs[i][j];
      }
    }
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
  }

  // 空间优化
  int __minCost(vector<vector<int>> &costs)
  {
    int n = costs.size();
    vector<int> dp(3);
    for (int j = 0; j < 3; j++)
    {
      dp[j] = costs[0][j];
    }
    for (int i = 1; i < n; i++)
    {
      vector<int> next(3);
      for (int j = 0; j < 3; j++)
      {
        next[j] = std::min(dp[(j + 1) % 3], dp[(j + 2) % 3]) + costs[i][j];
      }
      dp.swap(next);
    }
    return *min_element(dp.begin(), dp.end());
  }
};

void test()
{
  Solution s;
  vector<vector<int>> c1 = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
  vector<vector<int>> c2 = {{7, 6, 2}};
  EXPECT_EQ_INT(10, s.minCost(c1));
  EXPECT_EQ_INT(2, s.minCost(c2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
