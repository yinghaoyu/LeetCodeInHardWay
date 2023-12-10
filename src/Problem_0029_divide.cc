#include <cmath>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 不用 + 实现加法
  // 对于非进位部分
  // 1 + 1 = 0
  // 1 + 0 = 1
  // 0 + 0 = 0
  // 0 + 1 = 1
  // 这相当于异或^
  // 对于进位部分只有 1 + 1 = 1，这相当于与&
  // 举个10进制的例子
  // 57 + 44 ：个位 7+4 >=10, 进位 1, 十位 5 + 4 < 10,进位 0,
  // 那么进位的部分就是 10, 为什么是 10 而不是 1 呢? 因为进位本来就是向高的地方进位, 所以要 "左移一位"
  // 非进位的那部分, 个位为 1, 十位为 9, 所以就是 91, 那么结果就是 91 + 10, 好, 那么现在问题就转换成了 91 + 10 了
  // 91 + 10：再次调用之前的操作, 进位的部分是 100, 非进位的部分是1, 那么就是 100 + 1
  // 100 + 1：进位的部分为0，非进位部分为 101，至此，检测到进位部分为 0 ，则计算结束。
  int add(int a, int b)
  {
    int sum = a;
    // 当检查到进位位为0，说明加法结束
    while (b != 0)
    {
      // 非进位部分
      sum = a ^ b;
      // 进位部分要往左移1位
      b = static_cast<unsigned int>(a & b) << 1;
      a = sum;
    }
    return sum;
  }

  // 这个函数要求 n 不能为INT32_MIN
  // 对 INT32_MIN 取负，还是INT32_MIN，显然不符合预期
  int neg(int n) { return add(~n, 1); }

  int sub(int a, int b) { return add(a, neg(b)); }

  int multi(int a, int b)
  {
    int ans = 0;
    // 模拟乘法运算
    while (b != 0)
    {
      if ((b & 1) != 0)
      {
        // 检查最低位
        ans = add(ans, a);
      }
      a = static_cast<unsigned int>(a) << 1;
      b = static_cast<unsigned int>(b) >> 1;  // 无符号右移
    }
    return ans;
  }

  bool isNeg(int n) { return n < 0; }

  // 必须保证 a 和 b 都不是整数最小值
  // 因为整数最小值不能转成自己的绝对值
  int div(int a, int b)
  {
    // 这里要求 a 和 b 均不能为 INT32_MIN
    int x = isNeg(a) ? neg(a) : a;
    int y = isNeg(b) ? neg(b) : b;
    int res = 0;
    // 把 x 想象成 x = y * 2^i + y * 2^(i-1) + ... + y * 2^1 + y * 2^0
    // 其中 i 为 x 的 bit 位
    // 检查 x 的每一位，依次从高位到低位检查
    // 由于 x >= 0，所以 i 取 31 或 30 开始都行
    for (int i = 31; i > neg(1); i = sub(i, 1))
    {
      // 第 i 个 bit 位不为0，说明存在因子 y * 2^i
      if ((x >> i) >= y)
      {
        // 把结果置上第 i 个 bit 位
        res |= (1 << i);
        // x 减去 y * 2^i，然后检查更低位的因子
        x = sub(x, y << i);
      }
    }
    return isNeg(a) ^ isNeg(b) ? neg(res) : res;
  }

  int divide(int dividend, int divisor)
  {
    if (divisor == INT32_MIN)
    {
      return dividend == INT32_MIN ? 1 : 0;
    }
    // 除数不是系统最小
    if (dividend == INT32_MIN)
    {
      if (divisor == neg(1))
      {
        // a 是整数最小，b 是 -1，返回整数最大
        return INT32_MAX;
      }
      // 由于 INT32_MIN 不能计算绝对值，因此可以先加一个offset(这里取1)，使得可以使用 div(a, b)

      // 先算出 (INT32_MIN + 1) / divisor 的商
      int ans = div(add(dividend, 1), divisor);
      // 然后计算 (dividend - ans * divisor) / divisor 的商
      // 再将两者相加
      return add(ans, div(sub(dividend, multi(ans, divisor)), divisor));
    }
    // dividend不是系统最小，divisor也不是系统最小
    return div(dividend, divisor);
  }
};

void testDevide()
{
  Solution s;
  EXPECT_EQ_INT(3, s.divide(10, 3));
  EXPECT_EQ_INT(-2, s.divide(7, -3));
  EXPECT_SUMMARY;
}

int main()
{
  testDevide();
  return 0;
}
