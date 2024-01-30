#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> getSum(vector<int>& arr)
  {
    int n = arr.size();
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++)
    {
      sum[i + 1] = sum[i] + arr[i];
    }
    return sum;
  }

  // L...R范围上，每次合并K个数，一定要合成出part个数，最小代价是多少
  int f(vector<int>& arr,
        int L,
        int R,
        int K,
        int part,
        vector<int>& sum,
        vector<vector<vector<int>>>& dp)
  {
    if (dp[L][R][part] != 0)
    {
      return dp[L][R][part];
    }
    if (L == R)
    {
      // 只剩1个数，如果 part == 1，无需合并，代价为0，否则无法合并
      dp[L][R][part] = (part == 1 ? 0 : -1);
      return dp[L][R][part];
    }
    if (part == 1)
    {
      // 说明最后一次必然合并K部分，这样下次才能合并成一个数
      int pre = f(arr, L, R, K, K, sum, dp);
      if (pre == -1)
      {
        dp[L][R][part] = -1;
        return -1;
      }
      dp[L][R][part] = pre + sum[R + 1] - sum[L];
      return dp[L][R][part];
    }
    int ans = INT32_MAX;
    // 枚举所有可能的情况
    for (int i = L; i < R; i += (K - 1))
    {
      int left = f(arr, L, i, K, 1, sum, dp);
      int right = f(arr, i + 1, R, K, part - 1, sum, dp);
      if (left != -1 && right != -1)
      {
        ans = std::min(ans, right + left);
      }
      else
      {
        dp[L][R][part] = -1;
      }
    }
    dp[L][R][part] = ans;
    return ans;
  }

  // 暴力递归 + 记忆化搜索
  int mergeStones(vector<int>& stones, int k)
  {
    int n = stones.size();
    // 最后一次必然拿走k个，之前每次拿走k-1个
    if ((n - 1) % (k - 1) != 0)
    {
      return -1;
    }
    vector<int> sum = getSum(stones);
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1)));
    return f(stones, 0, n - 1, k, 1, sum, dp);
  }

  // 递归改动态规划
  int dp(vector<int>& stones, int k)
  {
    int n = stones.size();
    if ((n - 1) % (k - 1) != 0)
    {
      return -1;
    }
    vector<int> sum = getSum(stones);
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, INT32_MAX)));
    for (int i = 0; i < n; i++)
    {
      // 只有1个数，合并成1个，成本为0
      dp[i][i][1] = 0;
    }
    // for (int l = 0; l < n ; l++)
    // {
    //  for (int r = l + 1; r < n; r++)
    //  {
    //  这种枚举有问题，当你计算dp[l][r][t]时，dp[p + 1][r][t - 1]是没有计算的 !!!
    //  }
    // }
    for (int len = 2; len <= n; len++)
    {
      for (int l = 0; l < n && l + len - 1 < n; l++)
      {
        int r = l + len - 1;
        for (int t = 2; t <= k; t++)
        {
          for (int p = l; p < r; p += k - 1)
          {
            dp[l][r][t] = std::min(dp[l][r][t], dp[l][p][1] + dp[p + 1][r][t - 1]);
          }
        }
        dp[l][r][1] = std::min(dp[l][r][1], dp[l][r][k] + sum[r + 1] - sum[l]);
      }
    }
    return dp[0][n - 1][1];
  }
};

void testMergeStones()
{
  Solution s;
  vector<int> s1 = {3, 2, 4, 1};
  vector<int> s2 = {3, 2, 4, 1};
  vector<int> s3 = {3, 5, 1, 2, 6};
  EXPECT_EQ_INT(20, s.mergeStones(s1, 2));
  EXPECT_EQ_INT(-1, s.mergeStones(s2, 3));
  EXPECT_EQ_INT(25, s.mergeStones(s3, 3));
  EXPECT_EQ_INT(20, s.dp(s1, 2));
  EXPECT_EQ_INT(-1, s.dp(s2, 3));
  EXPECT_EQ_INT(25, s.dp(s3, 3));
  EXPECT_SUMMARY;
}

int main()
{
  testMergeStones();
  return 0;
}
