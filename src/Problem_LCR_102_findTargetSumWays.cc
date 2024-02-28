#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/target-sum/
// @sa Problem_0494_findTargetSumWays.cc
class Solution
{
 public:
  int findTargetSumWays(vector<int>& nums, int target)
  {
    int sum = 0;
    for (int num : nums)
    {
      sum += num;
    }
    if (target < -sum || target > sum)
    {
      return 0;
    }
    int n = nums.size();
    int m = 2 * sum + 1;
    vector<vector<int>> dp(n + 1, vector<int>(m));
    dp[n][target + sum] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = -sum; j <= sum; j++)
      {
        if (j - nums[i] + sum >= 0)
        {
          dp[i][j + sum] += dp[i + 1][j - nums[i] + sum];
        }
        if (j + nums[i] + sum < m)
        {
          dp[i][j + sum] += dp[i + 1][j + nums[i] + sum];
        }
      }
    }
    return dp[0][sum];
  }
};
