#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 查找5的个数
  int getCount(long x)
  {
    int ans = 0;
    while (x != 0)
    {
      ans += x / 5;
      x /= 5;
    }
    return ans;
  }

  long f(int k)
  {
    long l = 0;
    long r = 1e10;
    int index = -1;
    while (l <= r)
    {
      long m = l + ((r - l) >> 1);
      if (getCount(m) <= k)
      {
        // 当满足<=条件时，让区间的左边界右移
        index = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    // 返回的是<=最右边的位置
    return index;
  }

  int preimageSizeFZF(int k)
  {
    if (k == 0)
    {
      return 5;
    }
    return f(k) - f(k - 1);
  }
};

void testPreimageSizeFZF()
{
  Solution s;
  EXPECT_EQ_INT(5, s.preimageSizeFZF(0));
  EXPECT_EQ_INT(0, s.preimageSizeFZF(5));
  EXPECT_EQ_INT(5, s.preimageSizeFZF(3));
  EXPECT_EQ_INT(5, s.preimageSizeFZF(25));
  EXPECT_EQ_INT(5, s.preimageSizeFZF(45));
  EXPECT_SUMMARY;
}

int main()
{
  testPreimageSizeFZF();
  return 0;
}
