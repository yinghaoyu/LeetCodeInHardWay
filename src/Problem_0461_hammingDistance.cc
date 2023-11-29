#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  int countBit(int n)
  {
    n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
    return n;
  }

 public:
  int hammingDistance(int x, int y)
  {
    // 异或求不同 bit 位差异
    return countBit(x ^ y);
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(2, s.hammingDistance(1, 4));
  EXPECT_EQ_INT(1, s.hammingDistance(3, 1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
