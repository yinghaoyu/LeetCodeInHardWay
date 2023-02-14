#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  double myPow(double x, int n)
  {
    if (n == 0)
    {
      return 1.0;
    }
    if (n == INT32_MIN)
    {
      return (x == 1.0 || x == -1.0) ? 1.0 : 0;
    }
    double ans = 1;
    for (int i = std::abs(n); i != 0; i = i >> 1)
    {
      if (i & 1)
      {
        ans *= x;
      }
      x *= x;
    }
    return n < 0 ? 1 / ans : ans;
  }

  double dfs(double x, int n)
  {
    if (n == 0)
    {
      return 1.0;
    }
    else if (n & 1)
    {
      return (n > 0 ? x : 1.0 / x) * myPow(x * x, n / 2);
    }
    else
    {
      return myPow(x * x, n / 2);
    }
  }
};

void testMyPow()
{
  Solution s;
  // cout << s.myPow(2.00000, 10)<<endl;
  // cout << s.myPow(2.10000, 3)<<endl;
  // cout << s.myPow(2.00000, -1)<<endl;
  // cout << s.myPow(2.00000, -2)<<endl;
  // cout << s.dfs(2.00000, 10) << endl;
  // cout << s.dfs(2.10000, 3) << endl;
  // cout << s.dfs(2.00000, -1) << endl;
  // cout << s.dfs(2.00000, -2) << endl;
  EXPECT_EQ_DOUBLE(1024.00000, s.myPow(2.00000, 10));
  EXPECT_EQ_DOUBLE(9.26100, s.myPow(2.10000, 3));
  EXPECT_EQ_DOUBLE(0.50000, s.myPow(2.00000, -1));
  EXPECT_EQ_DOUBLE(0.25000, s.myPow(2.00000, -2));
  EXPECT_SUMMARY;
}

int main()
{
  testMyPow();
  return 0;
}
