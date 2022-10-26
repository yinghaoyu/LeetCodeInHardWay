#include <iostream>
#include <vector>

using namespace std;

#include "UnitTest.h"

class Solution
{
 public:
  int maxSubArray1(vector<int> &nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    int N = nums.size();
    // dp[i]表示必须以i位置为结尾的子数组的最大和
    vector<int> dp(N);
    dp[0] = nums[0];
    int max = dp[0];
    for (int i = 1; i < N; i++)
    {
      // 如果0...i-1的子数组最大和为负数，那么dp[i]明显取arr[i]
      // 如果0...i-1的子数组最大和为正数，那么dp[i]明显取arr[i]+dp[i-1]
      dp[i] = dp[i - 1] > 0 ? dp[i - 1] + nums[i] : nums[i];
      max = std::max(max, dp[i]);
    }
    return max;
  }

  int cross(vector<int> &nums, int left, int mid, int right)
  {
    // 一定会包含 nums[mid] 这个元素
    int sum = 0;
    int leftSum = INT32_MIN;
    // 左半边包含 nums[mid] 元素，最多可以到什么地方
    // 走到最边界，看看最值是什么
    // 计算以 mid 结尾的最大的子数组的和
    for (int i = mid; i >= left; i--)
    {
      sum += nums[i];
      if (sum > leftSum)
      {
        leftSum = sum;
      }
    }
    sum = 0;
    int rightSum = INT32_MIN;
    // 右半边不包含 nums[mid] 元素，最多可以到什么地方
    // 计算以 mid+1 开始的最大的子数组的和
    for (int i = mid + 1; i <= right; i++)
    {
      sum += nums[i];
      if (sum > rightSum)
      {
        rightSum = sum;
      }
    }
    return leftSum + rightSum;
  }

  int process(vector<int> &nums, int left, int right)
  {
    if (left == right)
    {
      return nums[left];
    }
    int mid = left + ((right - left) >> 1);
    // 最大值在左边
    // 最大值在中间
    // 最大值在右边
    return std::max(cross(nums, left, mid, right), std::max(process(nums, left, mid), process(nums, mid + 1, right)));
  }

  // 分治法
  int maxSubArray2(vector<int> &nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    return process(nums, 0, nums.size() - 1);
  }

  // 动态规划空间优化
  int maxSubArray3(vector<int> &nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    int max = INT32_MIN;
    int cur = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      cur += nums[i];
      max = std::max(max, cur);
      cur = cur < 0 ? 0 : cur;
    }
    return max;
  }
};

void testMaxSubArray()
{
  Solution s;
  vector<int> n1 = {2, 1, -3, 4, -1, 2, 1, -5, 4};
  vector<int> n2 = {1};
  vector<int> n3 = {5, 4, -1, 7, 8};
  EXPECT_EQ_INT(6, s.maxSubArray1(n1));
  EXPECT_EQ_INT(1, s.maxSubArray1(n2));
  EXPECT_EQ_INT(23, s.maxSubArray1(n3));
  EXPECT_EQ_INT(6, s.maxSubArray2(n1));
  EXPECT_EQ_INT(1, s.maxSubArray2(n2));
  EXPECT_EQ_INT(23, s.maxSubArray2(n3));
  EXPECT_EQ_INT(6, s.maxSubArray3(n1));
  EXPECT_EQ_INT(1, s.maxSubArray3(n2));
  EXPECT_EQ_INT(23, s.maxSubArray3(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxSubArray();
  return 0;
}
