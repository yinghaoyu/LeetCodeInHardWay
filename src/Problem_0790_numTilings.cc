#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 蒙德里安的梦想
// https://github.com/yinghaoyu/algorithms/blob/master/dp/PavingTile.cc

class Solution
{
 public:
  // dp
  // 考虑这么一种平铺的方式：在第 i 列前面的正方形都被瓷砖覆盖，在第 i 列后面的正方形都没有被瓷砖覆盖（i 从 1 开始计数）。
  // 那么第 i 列的正方形有四种被覆盖的情况：
  // 0. 一个正方形都没有被覆盖，记为状态 0；
  // 1. 只有上方的正方形被覆盖，记为状态 1；
  // 2. 只有下方的正方形被覆盖，记为状态 2；
  // 3. 上下两个正方形都被覆盖，记为状态 3。
  int numTilings(int n)
  {
    int mod = 1e9 + 7;
    vector<vector<long long>> dp(n + 1, vector<long long>(4));
    // base case
    dp[0][3] = 1;
    for (int i = 1; i <= n; i++)
    {
      // 为什么这里不包含dp[i-1][0] ？
      // 因为此时放置的瓷砖，仅对第 i −1 列产生影响，不会对第 i 列产生影响，该决策所产生的方案数，已在 dp[i−1][X] 时被统计
      dp[i][0] = dp[i - 1][3] /*+ dp[i-1][0]*/;
      dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
      dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
      dp[i][3] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3]) % mod;
    }
    return dp[n][3];
  }
};

void testNumTilings()
{
  Solution s;
  EXPECT_EQ_INT(5, s.numTilings(3));
  EXPECT_EQ_INT(1, s.numTilings(1));
  EXPECT_SUMMARY;
}

int main()
{
  testNumTilings();
  return 0;
}
