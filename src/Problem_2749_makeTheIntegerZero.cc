#include <vector>

using namespace std;

class Solution
{
 public:
  int makeTheIntegerZero(int num1, int num2)
  {
    // 假设操作 k 次，那么相当于 num1 要减去 k 个 num2
    // ，然后判断剩下的数字能否由 k 个 2^i 组成，这里 k 个 i 不一定要相同。

    int k = 1;
    while (true)
    {
      long long x = num1 - static_cast<long long>(num2) * k;
      if (x < k)
      {
        return -1;
      }
      if (k >= __builtin_popcountll(x))
      {
        return k;
      }
      k++;
    }
  }
};
