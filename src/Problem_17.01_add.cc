#include <iostream>

using namespace std;

class Solution
{
 public:
  // 两个数相加，拆成 进位和 与 非进位和 相加
  // 当进位和为 0，没有进位，加法结束
  int add(int a, int b)
  {
    int sum = a;
    while (b != 0)
    {
      // 非进位和
      sum = a ^ b;
      // 进位和
      b = (a & b) << 1;
      a = sum;
    }
    return sum;
  }
};
