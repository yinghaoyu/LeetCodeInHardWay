#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 二分查找
  int nthMagicalNumber(int n, int a, int b)
  {
    const int mod = 1e9 + 7;
    // 最小公倍数 = a * b / gcd(a, b)
    int lcm = a * b / gcd(a, b);
    long long l = 0;
    // 假设a和b最小值为a
    // n * a 至少有 n 个数是满足 % a == 0 的魔法数，因为 % b == 0 的还没计算在内
    long long r = 1LL * std::min(a, b) * n;
    long long index = -1;
    // 由于满足单调性，所以可以二分查找
    while (l <= r)
    {
      long long m = l + (r - l) / 2;
      // 对于当前数m
      // 有 m / a 个满足 %a == 0的魔法数
      // 有 m / b 个满足 %b == 0的魔法数
      // 有 m / lcm 个同时满足 %a == 0 和 %b == 0的魔法数
      // m / a + m / b 明显会多计算一次 m / lcm
      long long cur = m / a + m / b - m / lcm;
      if (cur >= n)
      {
        index = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return index % mod;
  }

  // 最大公约数，辗转相除法
  // 设被除数为A，除数为B，商为C，余数为D
  // 那么有GCD(A, B) = GCD(B, D)
  // 证明:
  // 已知 A = B * C + D
  // 1. 假设A和B有相同的因数k，存在A = a * k，B = b * k
  // 则有 D = a * k - b * k * C = k * (a - b * C)，其中a - b * C一定为整数
  // 所以当A和B有相同的因数k时，D也有相同的因数k
  //
  // 2. 假设B和D有相同的因数v，存在B = b * v，D = d * v
  // 则有A = b * v * C + d * v = v * (b * C + d)，其中b * C + d一定为整数
  // 所以当B和D有相同的因数v时，A也有相同的因数v
  //
  // 结论：k = v
  // 即：被除数，除数，余数这三者在辗转相除算法运算过程中始终会保持因子相同这一特点
  int gcd(int a, int b) { return b > 0 ? gcd(b, a % b) : a; }
};

void testNthMagicalNumber()
{
  Solution s;
  EXPECT_EQ_INT(2, s.nthMagicalNumber(1, 2, 3));
  EXPECT_EQ_INT(6, s.nthMagicalNumber(4, 2, 3));
  EXPECT_EQ_INT(999720007, s.nthMagicalNumber(1000000000, 40000, 40000));
  EXPECT_SUMMARY;
}

int main()
{
  testNthMagicalNumber();
  return 0;
}
