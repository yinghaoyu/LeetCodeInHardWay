#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> countBits1(int n)
  {
    vector<int> ans(n + 1);
    for (int i = 0; i <= n; i++)
    {
      ans[i] = bitCount(i);
    }
    return ans;
  }

  // 动态规划
  vector<int> countBits2(int n)
  {
    vector<int> ans(n + 1);
    for (int i = 0; i <= n; i++)
    {
      // 当前 i = 0b000101 的 ans[i]
      // 可以由少一位数的 j = 0b00010 的 ans[j] 推出
      // 只要 ans[j] 加上新加的一位， 即 i 的最后一位的得到
      // 判断 i 的最后一位是否为 1，只要 i & 1 即可
      ans[i] = ans[i >> 1] + (i & 1);
    }
    return ans;
  }

  vector<int> countBits3(int n)
  {
    vector<int> ans(n + 1);
    for (int i = 0; i <= n; i++)
    {
      ans[i] = countOnes(i);
    }
    return ans;
  }

  int countOnes(int x)
  {
    // Brian Kernighan 算法的原理是：
    // 对于任意整数 x，令 x = x & (x−1)，该运算将 x 的二进制表示的最后一个 1 变成 0。
    // 因此，对 x 重复该操作，直到 x 变成 0，则操作次数即为 x 的「比特数」。
    int ones = 0;
    while (x > 0)
    {
      x &= (x - 1);
      ones++;
    }
    return ones;
  }

  int bitCount(int n)
  {
    int x = ((n >> 1) & 0x55555555) + (n & 0x55555555);
    x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
    x = ((x >> 4) & 0x0f0f0f0f) + (x & 0x0f0f0f0f);
    x = ((x >> 8) & 0x00ff00ff) + (x & 0x00ff00ff);
    x = ((x >> 16) & 0x0000ffff) + (x & 0x0000ffff);
    return x;
  }
};

void testCountBits()
{
  Solution s;
  vector<int> o1 = {0, 1, 1};
  vector<int> o2 = {0, 1, 1, 2, 1, 2};
  EXPECT_TRUE(o1 == s.countBits1(2));
  EXPECT_TRUE(o2 == s.countBits1(5));
  EXPECT_TRUE(o1 == s.countBits2(2));
  EXPECT_TRUE(o2 == s.countBits2(5));
  EXPECT_SUMMARY;
}

int main()
{
  testCountBits();
  return 0;
}
