#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 如果一个数字是3的某次幂，那么这个数一定只含有3这个质数因子
  // 1162261467是int型范围内，最大的3的幂，它是3的19次方
  // 这个1162261467只含有3这个质数因子，如果n也是只含有3这个质数因子，那么
  // 1162261467 % n == 0
  // 反之如果1162261467 % n != 0 说明n一定含有其他因子
  bool isPowerOfThree(int n) { return n > 0 && (int) pow(3, 19) % n == 0; }
};

void testIsPowerOfThree()
{
  Solution s;
  EXPECT_TRUE(s.isPowerOfThree(27));
  EXPECT_FALSE(s.isPowerOfThree(0));
  EXPECT_FALSE(s.isPowerOfThree(-1));
  EXPECT_SUMMARY;
}

int main()
{
  testIsPowerOfThree();
  return 0;
}
