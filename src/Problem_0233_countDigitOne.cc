#include "UnitTest.h"

using namespace std;

// 数位dp
// @sa 拓展题 Problem_1067_digitsCount.cc
class Solution
{
 public:
  int countDigitOne(int n) { return digitsCount(1, 0, n); }

  int digitsCount(int d, int a, int b) { return count(b, d) - count(a - 1, d); }

  int count(int num, int d)
  {
    int ans = 0;
    for (int right = 1, tmp = num, left, cur; tmp != 0; right *= 10, tmp /= 10)
    {
      left = tmp / 10;
      cur = tmp % 10;
      if (d == 0)
      {
        left--;
      }
      ans += left * right;
      if (cur > d)
      {
        ans += right;
      }
      else if (cur == d)
      {
        ans += num % right + 1;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(6, s.countDigitOne(13));
  EXPECT_EQ_INT(0, s.countDigitOne(0));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
