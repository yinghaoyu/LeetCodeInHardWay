#include <math.h>
#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 理论上的暴力解
  int process(int cur, int step, int tag)
  {
    if (std::abs(cur) > std::abs(tag))
    {
      return INT32_MAX;
    }
    if (cur == tag)
    {
      return step;
    }
    step++;
    int p1 = process(cur + step, step, tag);
    int p2 = process(cur - step, step, tag);
    return std::min(p1, p2);
  }

  int reachNumber1(int target) { return process(0, 0, target); }

  int reachNumber2(int target)
  {
    target = abs(target);
    int k = 0;
    while (target > 0)
    {
      k++;
      target -= k;
    }
    return target % 2 == 0 ? k : k + 1 + k % 2;
  }
};

void testReachNumber()
{
  Solution s;
  EXPECT_EQ_INT(3, s.reachNumber2(2));
  EXPECT_EQ_INT(2, s.reachNumber2(3));
  EXPECT_EQ_INT(4, s.reachNumber2(10));
  EXPECT_EQ_INT(7, s.reachNumber2(12));
  EXPECT_EQ_INT(8, s.reachNumber2(32));
  EXPECT_EQ_INT(15, s.reachNumber2(100));
  EXPECT_EQ_INT(32, s.reachNumber2(500));
  EXPECT_EQ_INT(44723, s.reachNumber2(-1000000000));
  EXPECT_SUMMARY;
}

int main()
{
  testReachNumber();
  return 0;
}
