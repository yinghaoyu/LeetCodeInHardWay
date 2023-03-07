#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力解
  int numSquares1(int n)
  {
    int ans = n;
    int num = 2;
    while (num * num <= n)
    {
      int a = n / (num * num);
      int b = n % (num * num);
      ans = std::min(ans, a + numSquares1(b));
      num++;
    }
    return ans;
  }

  // 1 : 1, 4, 9, 16, 25, 36, ...
  // 4 : 7, 15, 23, 28, 31, 39, 47, 55, 60, 63, 71, ...
  // 规律解
  // 规律一：个数不超过4
  // 规律二：出现1个的时候，显而易见
  // 规律三：任何数 % 8 == 7，一定是4个
  // 规律四：任何数消去4的因子之后，剩下rest，rest % 8 == 7，一定是4个
  int numSquares2(int n)
  {
    // TODO: figure it out
    int rest = n;
    while (rest % 4 == 0)
    {
      rest /= 4;
    }
    if (rest % 8 == 7)
    {
      return 4;
    }
    int f = (int) sqrt(n);
    if (f * f == n)
    {
      return 1;
    }
    for (int first = 1; first * first <= n; first++)
    {
      int second = (int) sqrt(n - first * first);
      if (first * first + second * second == n)
      {
        return 2;
      }
    }
    return 3;
  }

  // 数学解
  // 1）四平方和定理
  // 2）任何数消掉4的因子，结论不变
  int numSquares3(int n)
  {
    // TODO: figure it out
    while (n % 4 == 0)
    {
      n /= 4;
    }
    if (n % 8 == 7)
    {
      return 4;
    }
    for (int a = 0; a * a <= n; ++a)
    {
      int b = (int) sqrt(n - a * a);
      if (a * a + b * b == n)
      {
        return (a > 0 && b > 0) ? 2 : 1;
      }
    }
    return 3;
  }
};

void testNumSquares()
{
  Solution s;
  EXPECT_EQ_INT(3, s.numSquares1(12));
  EXPECT_EQ_INT(2, s.numSquares1(13));
  EXPECT_EQ_INT(3, s.numSquares2(12));
  EXPECT_EQ_INT(2, s.numSquares2(13));
  EXPECT_EQ_INT(3, s.numSquares3(12));
  EXPECT_EQ_INT(2, s.numSquares3(13));
  EXPECT_SUMMARY;
}

int main()
{
  testNumSquares();
  return 0;
}
