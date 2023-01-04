#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // len 为数组长度，max为数组中的最大值
  double sum(int len, long max)
  {
    double ans = 0;
    if (max > len)
    {
      // 数组为 max - len + 1 到max的等差数列
      ans = (max + max - len + 1) * len / 2;
    }
    else
    {
      // 数组一部分为1到max的等差数列，多余的len-max部分填1
      ans = (max + 1) * max / 2 + len - max;
    }
    return ans;
  }

  int maxValue(int n, int index, int maxSum)
  {
    long l = 1;
    long r = maxSum;
    long i = -1;
    while (l <= r)
    {
      long m = l + (r - l) / 2;
      // 设index位置的值为 m
      // 左边数组区间[0, index] 右边数组区间[index, end]
      // 整个数组的和 为两段数组的和 减去重复的index位置的值
      double ans = sum(index + 1, m) + sum(n - index, m) - m;
      if (ans <= maxSum)
      {
        i = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return i;
  }
};

void testMaxValue()
{
  Solution s;
  EXPECT_EQ_INT(2, s.maxValue(4, 2, 6));
  EXPECT_EQ_INT(3, s.maxValue(6, 1, 10));
  EXPECT_EQ_INT(11, s.maxValue(2, 1, 21));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxValue();
  return 0;
}
