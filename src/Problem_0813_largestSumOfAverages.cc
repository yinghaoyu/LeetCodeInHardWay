#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  double largestSumOfAverages(vector<int> &nums, int k)
  {
    int n = nums.size();
    // 前缀和优化
    vector<double> sum(n);
    sum[0] = nums[0];
    for (int i = 1; i < n; i++)
    {
      sum[i] = sum[i - 1] + nums[i];
    }
    // dp[i][k] 表示：将 nums 中的前 i 个数分成 k 个子数组的最大平均值总和
    vector<vector<double>> dp(n + 1, vector<double>(k + 1));
    // base case: k = 1，如果分一组
    for (int i = 1; i <= n; i++)
    {
      dp[i][1] = sum[i - 1] / i;
    }
    // dp
    for (int i = 1; i <= n; i++)
    {
      for (int m = 2; m <= k; m++)
      {
        for (int j = 1; j < i; j++)
        {
          // 第 i 个数的下标为 i - 1
          // * * * * * * * *
          //     ↑     ↑
          //     j     i-1
          // 取 j < i，则递推公式有
          // dp[i][m] = std::max(dp[i][m], dp[j][m-1] + avg(j, i-1))
          // avg(j, i-1)为区间[j, i-1]的平均值
          double avg = (sum[i - 1] - sum[j - 1]) / (i - j);
          dp[i][m] = max(dp[i][m], dp[j][m - 1] + avg);
        }
      }
    }
    return dp[n][k];
  }
};

void testLargestSumOfAverages()
{
  Solution s;
  vector<int> n1 = {9, 1, 2, 3, 9};
  vector<int> n2 = {1, 2, 3, 4, 5, 6, 7};
  vector<int> n3 = {4, 1, 7, 5, 6, 2, 3};
  EXPECT_EQ_DOUBLE(20.00000, s.largestSumOfAverages(n1, 3));
  EXPECT_EQ_DOUBLE(20.50000, s.largestSumOfAverages(n2, 4));
  EXPECT_EQ_DOUBLE(18.16667, s.largestSumOfAverages(n3, 4));
  EXPECT_SUMMARY;
}

int main()
{
  testLargestSumOfAverages();
  return 0;
}
