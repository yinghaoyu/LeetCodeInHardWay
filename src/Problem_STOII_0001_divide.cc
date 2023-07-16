#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0029 相同
// https://leetcode-cn.com/problems/divide-two-integers/
// see at Problem_0029_divide.cc
class Solution
{
 public:
  int divide(int a, int b) { return 0; }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(7, s.divide(15, 2));
  EXPECT_EQ_INT(-1, s.divide(7, -3));
  EXPECT_EQ_INT(0, s.divide(0, -1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
