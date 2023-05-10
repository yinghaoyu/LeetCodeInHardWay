#include <iostream>
#include <unordered_set>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 当 k 比较小时，用模拟方法
  int smallestRepunitDivByK1(int k)
  {
    // remainder(new) = ( n(new) * 10 + 1) % k
    //                = ( ( n(old) % k ) * 10 + 1) % k
    //                = ( remainder(old) * 10 + 1) % k
    //                所以过程中，只需要记录 remainder ，并且 remainder 范围在 [0, k)
    int remainder = 1 % k;
    int len = 1;
    unordered_set<int> set;
    while (remainder != 0)
    {
      remainder = (remainder * 10 + 1) % k;
      len++;
      if (set.count(remainder))
      {
        return -1;
      }
      set.insert(remainder);
    }
    return len;
  }

  int smallestRepunitDivByK2(int k)
  {
    // 若 k 能被 2 或 5 整除，则无解，返回 -1
    if (k % 2 == 0 || k % 5 == 0)
    {
      return -1;
    }
    // 初始化余数为 1，表示一个数的最低位是 1
    int resid = 1 % k, len = 1;
    // 若余数不为 0，继续迭代
    while (resid != 0)
    {
      // 计算下一个数的余数，下一个数在当前余数后加一个 1
      resid = (resid * 10 + 1) % k;
      len++;
    }
    // 返回数字 1 的最小重复次数
    return len;
  }
};

void testSmallestRepunitDivByK()
{
  Solution s;
  EXPECT_EQ_INT(1, s.smallestRepunitDivByK1(1));
  EXPECT_EQ_INT(-1, s.smallestRepunitDivByK1(2));
  EXPECT_EQ_INT(3, s.smallestRepunitDivByK1(3));
  EXPECT_EQ_INT(9, s.smallestRepunitDivByK1(9));
  EXPECT_EQ_INT(1, s.smallestRepunitDivByK2(1));
  EXPECT_EQ_INT(-1, s.smallestRepunitDivByK2(2));
  EXPECT_EQ_INT(3, s.smallestRepunitDivByK2(3));
  EXPECT_EQ_INT(9, s.smallestRepunitDivByK2(9));
  EXPECT_SUMMARY;
}

int main()
{
  testSmallestRepunitDivByK();
  return 0;
}
