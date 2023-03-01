#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int hammingWeight(uint32_t n)
  {
    int x = (n & 0x55555555) + ((n >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
    x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
    return x;
  }
};

void testHammingWeight()
{
  Solution s;
  EXPECT_EQ_INT(3, s.hammingWeight(0b00000000000000000000000000001011));
  EXPECT_EQ_INT(1, s.hammingWeight(0b00000000000000000000000010000000));
  EXPECT_EQ_INT(31, s.hammingWeight(0b11111111111111111111111111111101));
  EXPECT_SUMMARY;
}

int main()
{
  testHammingWeight();
  return 0;
}
