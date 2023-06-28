#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numberOfCuts(int n)
  {
    if (n == 1)
    {
      return 0;
    }
    else if (n & 1)
    {
      return n;
    }
    else
    {
      return n / 2;
    }
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(0, s.numberOfCuts(1));
  EXPECT_EQ_INT(2, s.numberOfCuts(4));
  EXPECT_EQ_INT(3, s.numberOfCuts(3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
