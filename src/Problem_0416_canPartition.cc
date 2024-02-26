#include <vector>

using namespace std;

class Solution
{
 public:
  bool canPartition(vector<int>& nums)
  {
    if (nums.size() < 2)
    {
      // 元素数量不够拆分
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
      // 有余数，不能拆分
      return false;
    }
    int target = sum / 2;
    if (max > target)
    {
      // 元素过大不能拆分
      return false;
    }
    int n = nums.size();
    // dp[i][j]的含义为：取出nums[0...i]范围内的任意个元素，能否拼出和为 j
    vector<vector<bool>> dp(n, vector<bool>(target + 1));
    // 注意：这里需要满足 nums[0] <= target，这就是前面需要判断 max > target的原因
    dp[0][nums[0]] = true;
    for (int i = 0; i < n; i++)
    {
      // 和为 0 一直可以取到
      dp[i][0] = true;
    }
    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= target; j++)
      {
        if (j - nums[i] >= 0)
        {
          // 可不取、可取 nums[i]
          dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
        }
        else
        {
          // 不取 nums[i]
          dp[i][j] = dp[i - 1][j];
        }
      }
    }
    return dp[n - 1][target];
  }
};
