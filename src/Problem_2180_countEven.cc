#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countEven(int num)
  {
    int ans = 0;
    for (int i = 2; i <= num; i++)
    {
      int sum = 0;
      int x = i;
      while (x)
      {
        sum += x % 10;
        x /= 10;
      }
      if (!(sum & 1))
      {
        ans++;
      }
    }
    return ans;
  }
};

void testCountEven()
{
  Solution s;
  EXPECT_EQ_INT(2, s.countEven(4));
  EXPECT_EQ_INT(14, s.countEven(30));
  EXPECT_SUMMARY;
}

int main()
{
  testCountEven();
  return 0;
}
