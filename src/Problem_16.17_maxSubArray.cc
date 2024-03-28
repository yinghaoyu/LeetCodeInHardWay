#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int maxSubArray1(vector<int>& nums)
  {
    int n = nums.size();
    // dp[i]表示的含义为，必须以nums[i]为结尾的序列最大和
    vector<int> dp(n);
    dp[0] = nums[0];
    int ans = dp[0];
    for (int i = 1; i < n; i++)
    {
      dp[i] = dp[i - 1] > 0 ? dp[i - 1] + nums[i] : nums[i];
      ans = std::max(ans, dp[i]);
    }
    return ans;
  }

  class Info
  {
   public:
    int lSum;  // 表示[l, r]区间内必须以l为左端点的最大子段和
    int rSum;  // 表示[l, r]区间内必须以r为右端点的最大子段和
    int mSum;  // 表示[l, r]区间内最大子段和
    int iSum;  // 表示[l, r]区间和
  };

  Info f(vector<int>& arr, int l, int r)
  {
    if (l == r)
    {
      return {arr[l], arr[l], arr[l], arr[l]};
    }
    int m = (r - l) / 2 + l;
    Info left = f(arr, l, m);
    Info right = f(arr, m + 1, r);
    int lSum = std::max(left.lSum, left.iSum + right.lSum);
    int rSum = std::max(right.rSum, right.iSum + left.rSum);
    int iSum = left.iSum + right.iSum;
    // 两种情况，包含中点，不包含中点
    int mSum = std::max({left.mSum, right.mSum, left.rSum + right.lSum});
    return {lSum, rSum, mSum, iSum};
  }

  // 分治法
  int maxSubArray2(vector<int>& nums) { return f(nums, 0, nums.size() - 1).mSum; }
};
