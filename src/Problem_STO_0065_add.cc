#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int add(int a, int b)
  {
    int sum = a;
    while (b != 0)
    {
      sum = a ^ b;
      b = static_cast<unsigned int>(a & b) << 1;
      a = sum;
    }
    return sum;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(2, s.add(1, 1));
  EXPECT_EQ_INT(4, s.add(-1, 5));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
