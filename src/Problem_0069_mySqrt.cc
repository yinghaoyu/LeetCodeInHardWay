#include <iostream>
#include <vector>

#include "UnitTest.h"
class Solution
{
 public:
  // x一定非负，输入可以保证
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
    long ans = 1;
    long L = 1;
    long R = x;
    long M = 0;
    while (L <= R)
    {
      M = (L + R) / 2;
      if (M * M <= x)
      {
        ans = M;
        L = M + 1;
      }
      else
      {
        R = M - 1;
      }
    }
    return (int) ans;
  }
};

void testMySqrt()
{
  Solution s;
  EXPECT_EQ_INT(2, s.mySqrt(4));
  EXPECT_EQ_INT(2, s.mySqrt(8));
  EXPECT_SUMMARY;
}

int main()
{
  testMySqrt();
  return 0;
}
