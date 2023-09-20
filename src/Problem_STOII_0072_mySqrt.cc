#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/sqrtx/
// @sa Problem_0069_mySqrt.cc

class Solution
{
 public:
  int mySqrt(int x)
  {
    if (x == 0)
    {
      return 0;
    }
    if (x < 3)
    {
      return 1;
    }
    long long ans = 1;
    long long left = 1;
    long long right = x;
    while (left <= right)
    {
      long long mid = (right - left) / 2 + left;
      if (mid * mid <= x)
      {
        ans = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return ans;
  }
};
