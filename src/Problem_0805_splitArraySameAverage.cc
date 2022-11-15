#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isEuqal(double a, double b) { return std::abs(a - b) < 1e-5; }

  // 二进制枚举
  bool splitArraySameAverage1(vector<int> &nums)
  {
    int n = nums.size();
    int mask = 1 << n;
    for (int i = 0; i < mask; i++)
    {
      int a = 0;
      int l1 = 0;
      int b = 0;
      int l2 = 0;
      for (int j = 0; j < n; j++)
      {
        if ((i >> j) & 1)
        {
          a += nums[j];
          l1++;
        }
        else
        {
          b += nums[j];
          l2++;
        }
      }
      if (l1 > 0 && l2 > 0 && isEuqal(static_cast<double>(a) / l1, static_cast<double>(b) / l2))
      {
        return true;
      }
    }
    return false;
  }

  bool splitArraySameAverage2(vector<int> &nums)
  {
    int n = nums.size(), m = n / 2;
    if (n == 1)
    {
      return false;
    }
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // 如果直接将 nums 中的每个元素减去数组和的平均值（sum/n），可能会引入浮点数，判断时出现误差
    // 所以这里先将 nums 的每个元素乘以 n，这样数组和的平均值则变为 sum （无需除以n），而 nums[i]*n-sum 一定为整数
    for (int &x : nums)
    {
      x = x * n - sum;
    }

    // 原题意等价于，能否从从nums的n个元素中找出m个元素累加和为0，m < n，因为另一个数组元素不能为空

    unordered_set<int> left;
    // 二进制枚举
    for (int i = 1; i < (1 << m); i++)
    {
      int tot = 0;
      for (int j = 0; j < m; j++)
      {
        if (i & (1 << j))
        {
          tot += nums[j];
        }
      }
      // 后半个数组有部分元素之和为0
      // 因为符合条件，不需要在找了
      if (tot == 0)
      {
        return true;
      }
      left.emplace(tot);
    }

    int rsum = accumulate(nums.begin() + m, nums.end(), 0);
    for (int i = 1; i < (1 << (n - m)); i++)
    {
      int tot = 0;
      for (int j = m; j < n; j++)
      {
        if (i & (1 << (j - m)))
        {
          tot += nums[j];
        }
      }
      // 情况一：后半个数组有部分元素之和为0
      // 情况二：前半个数组的子集的元素之和 是 后半个数组的子集的元素之和 的相反数时
      // 特殊情况：
      // 因为经过 x = x * n - sum 后，nums素组的累加和一定为0
      // 左半部分数组一定存在-rsum，这时A把所有元素选了，B就没有元素可选了，明显不符合题意
      if (tot == 0 || (rsum != tot && left.count(-tot)))
      {
        return true;
      }
    }
    return false;
  }

  bool splitArraySameAverage3(vector<int> &nums)
  {
    int n = nums.size(), m = n / 2;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // 假设选出的数组为A
    // sum(A) / len(A) = sum(nums) / len(nums)
    // sum(A) = sum(nums) * len(A) / len(nums) 必须为整数
    bool isPossible = false;
    for (int i = 1; i <= m; i++)
    {
      if (sum * i % n == 0)
      {
        isPossible = true;
        break;
      }
    }
    if (!isPossible)  // 剪枝
    {
      return false;
    }
    // dp[i][x] 表示当前已从数组 nums 取出 i 个元素构成的和为 x 的可能性
    // 则有dp[i + 1][x + nums[j]] = dp[i][x]

    // 这里用unordered_set是为了过滤重复值，剪枝
    vector<unordered_set<int>> dp(m + 1);
    // 选择0个元素，构成和为0
    dp[0].insert(0);
    for (int num : nums)  // 从左到右遍历数组
    {
      for (int i = m; i >= 1; i--)  // 剪枝，两个子数组其中一个长度一定 <= m
      {
        for (int x : dp[i - 1])
        {
          int curr = x + num;
          if (curr * n == sum * i)
          {
            return true;
          }
          dp[i].emplace(curr);
        }
      }
    }
    return false;
  }
};

void testSplitArraySameAverage()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 4, 5, 6, 7, 8};
  vector<int> n2 = {3, 1};
  vector<int> n3 = {6, 8, 18, 3, 1};
  EXPECT_TRUE(s.splitArraySameAverage1(n1));
  EXPECT_FALSE(s.splitArraySameAverage1(n2));
  EXPECT_FALSE(s.splitArraySameAverage1(n3));
  EXPECT_TRUE(s.splitArraySameAverage2(n1));
  EXPECT_FALSE(s.splitArraySameAverage2(n2));
  EXPECT_FALSE(s.splitArraySameAverage2(n3));
  EXPECT_TRUE(s.splitArraySameAverage3(n1));
  EXPECT_FALSE(s.splitArraySameAverage3(n2));
  EXPECT_FALSE(s.splitArraySameAverage3(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testSplitArraySameAverage();
  return 0;
}
