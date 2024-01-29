#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 普通解法的动态规划
  // 时间复杂度O(n^2)，数组稍大就会超时
  int dp(vector<int>& nums)
  {
    int n = nums.size();
    // dp[i]的含义为：必须以nums[i]为结尾的最大递增子序列的数量
    vector<int> dp(n);
    dp[0] = 1;
    int max = 1;
    for (int i = 0; i < n; i++)
    {
      dp[i] = 1;
      for (int j = 0; j < i; j++)
      {
        // 这一步用二分优化成O(logN) ？
        if (nums[j] < nums[i])
        {
          dp[i] = std::max(dp[i], dp[j] + 1);
        }
      }
      max = std::max(max, dp[i]);
    }
    return max;
  }

  // 贪心 + 二分
  int lengthOfLIS(vector<int>& nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    int n = nums.size();
    // ends 表示为长度为k+1的递增子序列尾部元素的值
    // ends 一定是严格递增的
    // 即当尽可能使每个子序列尾部元素值最小的前提下，子序列越长，其序列尾部元素值一定更大。
    // 满足单调性，所以可以用二分查找
    vector<int> ends(n);
    ends[0] = nums[0];
    int right = 0;
    int l = 0;
    int r = 0;
    int m = 0;
    int max = 1;
    for (int i = 1; i < nums.size(); i++)
    {
      l = 0;
      r = right;
      // 对原序列进行遍历，将每位元素二分插入 ends 中
      // 如果 ends 中元素都比它小，将它插到最后
      // 否则，用它覆盖掉比它大的元素中最小的那个
      // 思想就是让 ends 中存储比较小的元素
      while (l <= r)
      {
        m = (r - l) / 2 + l;
        if (nums[i] > ends[m])
        {
          l = m + 1;
        }
        else
        {
          r = m - 1;
        }
      }
      right = std::max(right, l);
      ends[l] = nums[i];
      max = std::max(max, l + 1);
    }
    return max;
  }
};

void testLengthOfLIS()
{
  Solution s;
  vector<int> n1 = {10, 9, 2, 5, 3, 7, 101, 18};
  vector<int> n2 = {0, 1, 0, 3, 2, 3};
  vector<int> n3 = {7, 7, 7, 7, 7, 7, 7};
  EXPECT_EQ_INT(4, s.dp(n1));
  EXPECT_EQ_INT(4, s.dp(n2));
  EXPECT_EQ_INT(1, s.dp(n3));
  EXPECT_EQ_INT(4, s.lengthOfLIS(n1));
  EXPECT_EQ_INT(4, s.lengthOfLIS(n2));
  EXPECT_EQ_INT(1, s.lengthOfLIS(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testLengthOfLIS();
  return 0;
}
