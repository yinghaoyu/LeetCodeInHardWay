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
    // 假设 right 为 0101001101
    // 如果 left < right - lowBit(right)
    // 那么必然存在值 0101001100 会把 0101001101 最左的 1 消掉
    // 这时 right 取 0101001100
    // 如果 left < right - lowBit(right)
    // 那么必然存在值 0101001011 会把 0101001100 最左的 1 消掉
    // 一直迭代下去
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
