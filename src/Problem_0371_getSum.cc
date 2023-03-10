#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int getSum(int a, int b)
  {
    int sum = a;
    while (b != 0)
    {
      sum = a ^ b;
      b = (a & b) << 1;
      a = sum;
    }
    return sum;
  }
};

void testGetSum()
{
  Solution s;
  EXPECT_EQ_INT(3, s.getSum(1, 2));
  EXPECT_EQ_INT(5, s.getSum(2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  testGetSum();
  return 0;
}
