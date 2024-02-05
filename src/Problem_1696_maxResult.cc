#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
  int f(vector<int>& arr, int i, int k, vector<int>& dp)
  {
    if (i == arr.size() - 1)
    {
      return arr.back();
    }
    if (dp[i] != INT32_MIN / 2)
    {
      return dp[i];
    }
    int ans = INT32_MIN / 2;
    for (int j = 1; j <= k && i + j < arr.size(); j++)
    {
      ans = std::max(ans, f(arr, i + j, k, dp) + arr[i]);
    }
    dp[i] = ans;
    return ans;
  }

 public:
  // 暴力递归，超时
  int maxResult(vector<int>& nums, int k)
  {
    vector<int> dp(nums.size(), INT32_MIN / 2);
    return f(nums, 0, k, dp);
  }

  // 动态规划，超时
  int dp(vector<int>& nums, int k)
  {
    int n = nums.size();
    vector<int> dp(n, INT32_MIN / 2);
    dp[n - 1] = nums.back();
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = 1; j <= k && i + j < n; j++)
      {
        dp[i] = std::max(dp[i], dp[i + j] + nums[i]);
      }
    }
    return dp[0];
  }

  // TODO: 单调队列优化
};
