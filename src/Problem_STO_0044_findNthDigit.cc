#include <cmath>
#include <iostream>
#include <vector>

// 与 leetcode 0400 题相同
// https://leetcode-cn.com/problems/nth-digit/
// see Problem_0400_findNthDigit.cc
class Solution
{
 public:
  int findNthDigit(int n)
  {
    int left = 1;
    int right = 9;
    while (left < right)
    {
      int mid = (right - left) / 2 + left;
      if (total(mid) < n)
      {
        left = mid + 1;
      }
      else
      {
        right = mid;
      }
    }
    int d = left;
    int pre = total(d - 1);
    int idx = n - pre - 1;
    int start = pow(10, d - 1);
    int num = start + idx / d;
    int offset = idx % d;
    int digit = num / static_cast<int>(pow(10, d - offset - 1)) % 10;
    return digit;
  }

  int total(int len)
  {
    int sum = 0;
    int curLen = 1;
    int curCount = 9;
    while (curLen <= len)
    {
      sum += curLen * curCount;
      curLen++;
      curCount *= 10;
    }
    return sum;
  }
};
