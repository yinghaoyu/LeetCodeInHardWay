#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/partition-equal-subset-sum/
// @sa Problem_0416_canPartition.cc
class Solution
{
 public:
  bool canPartition(vector<int>& nums)
  {
    if (nums.size() < 2)
    {
      return false;
    }
    int sum = 0;
    int max = 0;
    for (int num : nums)
    {
      max = std::max(num, max);
      sum += num;
    }
    if (sum % 2 != 0)
    {
      return false;
    }
    int target = sum / 2;
    if (max > target)
    {
      return false;
    }
    int n = nums.size();
    vector<vector<bool>> dp(n, vector<bool>(target + 1));
    dp[0][nums[0]] = true;
    for (int i = 0; i < n; i++)
    {
      dp[i][0] = true;
    }
    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= target; j++)
      {
        if (j - nums[i] >= 0)
        {
          dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
        }
        else
        {
          dp[i][j] = dp[i - 1][j];
        }
      }
    }
    return dp[n - 1][target];
  }
};
