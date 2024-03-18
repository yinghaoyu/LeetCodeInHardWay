#include <vector>

using namespace std;

class Solution
{
 public:
  // 模拟乘法
  int f(int A, int B)
  {
    if (B == 0)
    {
      return 0;
    }

    if (B & 1)
    {
      // B 的低位非 0， 说明需要加上这项
      return A + f(A << 1, B >> 1);
    }

    return f(A << 1, B >> 1);
  }

  int multiply(int A, int B) { return f(A, B); }
};
