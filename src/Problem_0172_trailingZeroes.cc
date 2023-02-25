#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int trailingZeroes(int n)
  {
    int ans = 0;
    while (n != 0)
    {
      n /= 5;
      ans += n;
    }
    return ans;
  }
};

void testTrailingZeroes()
{
  Solution s;
  EXPECT_EQ_INT(0, s.trailingZeroes(3));
  EXPECT_EQ_INT(1, s.trailingZeroes(5));
  EXPECT_EQ_INT(0, s.trailingZeroes(0));
  EXPECT_SUMMARY;
}

int main()
{
  testTrailingZeroes();
  return 0;
}
