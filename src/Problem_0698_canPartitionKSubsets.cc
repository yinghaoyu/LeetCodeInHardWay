#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 记忆化搜索
  // 由于数组长1~16，state每1位bit表示数组元素有没有使用，二进制枚举
  // pre 表示前面元素的累加和
  // dp
  bool process(vector<int> &nums, int state, int pre, int avg, vector<bool> &dp)
  {
    if (state == 0)
    {
      // 所有元素都被使用
      return true;
    }
    if (!dp[state])
    {
      return dp[state];
    }
    dp[state] = false;  // 初始时只要state不是0，都是false
    for (int i = 0; i < nums.size(); i++)
    {
      if (nums[i] + pre > avg)
      {
        // 前面元素累加和 + 当前元素 > avg
        // nums已经有序，下一个元素一定更大，说明不用尝试了 !
        break;
      }
      if ((state >> i) & 1)  // 当前i位置的元素未使用
      {
        // 这里 % 的作用是，当 pre + num[i] == avg 的时候清0
        if (process(nums, state ^ (1 << i), ((pre + nums[i]) % avg), avg, dp))
        {
          dp[state] = true;
          break;
        }
      }
    }
    return dp[state];
  }

  bool canPartitionKSubsets(vector<int> &nums, int k)
  {
    int sum = 0;
    int N = nums.size();
    for (int i = 0; i < N; i++)
    {
      sum += nums[i];
    }
    int avg = sum / k;
    if (avg * k != sum)
    {
      return false;
    }
    std::sort(nums.begin(), nums.end());
    if (nums.back() > avg)
    {
      return false;
    }
    // dp[i]表示示在可用的数字状态为 i 的情况下是否可行
    // 这里的初值用false，结果没错，但会超时
    vector<bool> dp(1 << N, true);
    return process(nums, (1 << N) - 1, 0, avg, dp);
  }

  bool dp(vector<int> &nums, int k)
  {
    int sum = 0;
    int N = nums.size();
    for (int i = 0; i < N; i++)
    {
      sum += nums[i];
    }
    int avg = sum / k;
    if (avg * k != sum)
    {
      return false;
    }
    std::sort(nums.begin(), nums.end());
    if (nums.back() > avg)
    {
      return false;
    }
    int M = 1 << N;
    vector<int> dp(M, false);
    vector<int> pre(M, 0);
    dp[0] = true;                // 所有元素都被使用
    for (int i = 0; i < M; i++)  // state
    {
      if (!dp[i])
      {
        continue;
      }
      for (int j = 0; j < N; j++)  // 尝试
      {
        if (pre[i] + nums[j] > avg)
        {
          break;
        }
        if (((i >> j) & 1) == 0)  // i状态下，数组的第j元素未使用
        {
          int next = i | (1 << j);
          if (!dp[next])
          {
            pre[next] = (pre[i] + nums[j]) % avg;
            dp[next] = true;
          }
        }
      }
    }
    return dp[M - 1];
  }
};

void testCanPartitionKSubsets()
{
  Solution s;
  vector<int> arr1 = {4, 3, 2, 3, 5, 2, 1};
  vector<int> arr2 = {1, 2, 3, 4};
  vector<int> arr3 = {2, 2, 2, 2, 3, 4, 5};
  vector<int> arr4 = {18, 20, 39, 73, 96, 99, 101, 111, 114, 190, 207, 295, 471, 649, 700, 1037};
  EXPECT_TRUE(s.canPartitionKSubsets(arr1, 4));
  EXPECT_FALSE(s.canPartitionKSubsets(arr2, 3));
  EXPECT_FALSE(s.canPartitionKSubsets(arr3, 4));
  EXPECT_TRUE(s.canPartitionKSubsets(arr4, 4));

  EXPECT_TRUE(s.dp(arr1, 4));
  EXPECT_FALSE(s.dp(arr2, 3));
  EXPECT_FALSE(s.dp(arr3, 4));
  EXPECT_TRUE(s.dp(arr4, 4));
  EXPECT_SUMMARY;
}

int main()
{
  testCanPartitionKSubsets();
  return 0;
}
