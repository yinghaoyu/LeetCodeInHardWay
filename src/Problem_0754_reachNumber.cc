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
      // 令s1 = 1 + 2 + ... + k
      //   s2 = 1 + 2 + ... + k + (k+1)
      //   s3 = 1 + 2 + ... + k + (k+1) + (k+2)
      // 找到第一个s1，使得 s1 >= target
      // delta = s1 - target
      // delta为偶数，那么只需要从1..k之间找出和为 delta/2 的若干个数
      //  如果 k >= delta / 2，选出一个 delta/2 就行了
      //  如果 k < delta / 2，因为 delta / 2 < s1，所以一定能找到若干个数满足条件
      // delta为奇数，s2和s3必有一个和s的奇偶性相同，使得delta为偶数
      k++;
      target -= k;
    }
    // 观察可发现如下奇偶性规律
    // k : 奇 偶 奇 偶
    // s : 奇 奇 偶 偶
    // delta = s - target
    // 要改变delta的奇偶性，可以通过改变s
    // 对于偶数k，只需要 k+1 即可改变s的奇偶性
    // 对于奇数k，则需要 k+2 才可改变s的奇偶性
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
