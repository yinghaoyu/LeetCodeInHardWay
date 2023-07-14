#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<double> dicesProbability(int n)
  {
    // dp[i][j] 表示前 i 次摇骰子得到和为 j 的方法数
    vector<vector<int>> dp(n + 1, vector<int>(6 * n + 1));
    for (int j = 1; j <= 6; j++)
    {
      dp[1][j] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
      // 骰子和的最小值，如果摇了 i 次，每次都为 1，和为 i
      for (int j = i; j <= 6 * n; j++)
      {
        for (int k = 1; k <= 6; k++)
        {
          if (k > j)
          {
            continue;
          }
          // 前 i - 1 次和为 j - k，第 i 次摇 k
          dp[i][j] += dp[i - 1][j - k];
        }
      }
    }
    vector<double> ans;
    // 总共可能得结果
    double p = pow(6, n);

    for (int j = n; j <= 6 * n; j++)
    {
      ans.push_back((dp[n][j] / p));
    }
    return ans;
  }
};
