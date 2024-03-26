#include <cstdint>
#include <iostream>

using namespace std;

// @sa https://leetcode.cn/problems/divide-two-integers/
// @sa Problem_0029_divide.cc
class Operations
{
 public:
  Operations() {}

  int add(int a, int b)
  {
    int sum = a;
    // 模拟加法计算
    while (b != 0)
    {
      // 当前位
      sum = a ^ b;
      // 进位位
      b = (a & b) << 1;
      a = sum;
    }
    return sum;
  }

  int neg(int n) { return add(~n, 1); }

  int minus(int a, int b) { return add(a, neg(b)); }

  int multiply(int a, int b)
  {
    int ans = 0;
    // 模拟乘法计算
    while (b != 0)
    {
      if (b & 1)
      {
        ans = add(ans, a);
      }
      a <<= 1;
      // 这里需要无符号右移
      b = (unsigned int) b >> 1;
    }
    return ans;
  }

  bool isNeg(int n) { return n < 0; }

  // 这个函数不处理特殊情况
  int raw_divide(int a, int b)
  {
    // 为了计算方便，先转成正数计算
    int x = isNeg(a) ? neg(a) : a;
    int y = isNeg(b) ? neg(b) : b;
    int ans = 0;
    for (int i = 31; i > neg(1); i = minus(i, 1))
    {
      // 模拟除法计算
      if ((x >> i) >= y)
      {
        ans |= (1 << i);
        x = minus(x, y << i);
      }
    }
    // a 和 b 异号返回负数，否则返回正数
    return isNeg(a) ^ isNeg(b) ? neg(ans) : ans;
  }

  int divide(int a, int b)
  {
    if (b == INT32_MIN)
    {
      return a == INT32_MIN ? 1 : 0;
    }
    // 除数不是系统最小
    if (a == INT32_MIN)
    {
      if (b == neg(1))
      {
        // 未定义行为，取决于编译器，g++输出INT32_MIN
        return INT32_MIN;
      }
      // 这两步转化，主要是为了满足raw_divide的入参条件，即raw_divide不处理特殊情况
      // ans = (a + 1) / b
      // ans + (a - asn * b) / b
      int ans = raw_divide(add(a, 1), b);
      return add(ans, raw_divide(minus(a, multiply(ans, b)), b));
    }
    // a 不是系统最小，b 也不是系统最小
    return raw_divide(a, b);
  }
};

/**
 * Your Operations object will be instantiated and called as such:
 * Operations* obj = new Operations();
 * int param_1 = obj->minus(a,b);
 * int param_2 = obj->multiply(a,b);
 * int param_3 = obj->divide(a,b);
 */
