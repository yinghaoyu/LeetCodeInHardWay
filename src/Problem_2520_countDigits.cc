#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countDigits(int num)
  {
    int x = num;
    int ans = 0;
    while (x > 0)
    {
      if (num % (x % 10) == 0)
      {
        ans++;
      }
      x /= 10;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(1, s.countDigits(7));
  EXPECT_EQ_INT(2, s.countDigits(121));
  EXPECT_EQ_INT(4, s.countDigits(1248));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
