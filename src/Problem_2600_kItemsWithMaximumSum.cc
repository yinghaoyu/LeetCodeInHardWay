#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k)
  {
    if (k <= numOnes)
    {
      return k;
    }
    else if (k <= numOnes + numZeros)
    {
      return numOnes;
    }
    else
    {
      return numOnes - (k - numOnes - numZeros);
    }
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(2, s.kItemsWithMaximumSum(3, 2, 0, 2));
  EXPECT_EQ_INT(3, s.kItemsWithMaximumSum(3, 2, 0, 4));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
