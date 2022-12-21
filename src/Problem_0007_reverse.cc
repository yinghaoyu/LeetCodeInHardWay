#include <cmath>
#include <cstdint>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int reverse(int x)
  {
    bool neg = ((x >> 31) & 1);
    // 32位带符号数的表示范围为 [- 2^31, 2^31 - 1]
    // 因此
    // 2 ^ 31 - 1 可以转成 - 2^31 + 1
    // - 2 ^ 31 不可以转成 2 ^ 31
    // 所以考虑正数往负数转换
    x = neg ? x : -x;
    int m = INT32_MIN / 10;
    int n = INT32_MIN % 10;
    int ans = 0;
    while (x != 0)
    {
      if (ans < m || (ans == m && x % 10 < n))
      {
        // 溢出处理
        return 0;
      }
      ans = ans * 10 + x % 10;
      x /= 10;
    }
    return neg ? ans : std::abs(ans);
  }
};

void testReverse()
{
  Solution s;
  EXPECT_EQ_INT(321, s.reverse(123));
  EXPECT_EQ_INT(-321, s.reverse(-123));
  EXPECT_EQ_INT(21, s.reverse(120));
  EXPECT_SUMMARY;
}

int main()
{
  testReverse();
  return 0;
}
