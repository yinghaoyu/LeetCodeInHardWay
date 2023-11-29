#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  int lowBit(int x) { return x & -x; }

 public:
  int rangeBitwiseAnd(int left, int right)
  {
    while (left < right)
    {
      right -= lowBit(right);
    }
    return right;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(4, s.rangeBitwiseAnd(5, 7));
  EXPECT_EQ_INT(0, s.rangeBitwiseAnd(0, 0));
  EXPECT_EQ_INT(0, s.rangeBitwiseAnd(1, 2147483647));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
