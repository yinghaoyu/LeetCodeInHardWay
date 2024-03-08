#include <vector>

using namespace std;

class Solution
{
 public:
  // 为了让数组之和最小，我们按照 1,2,3,...的顺序考虑，
  // 但添加了 x 之后，就不能添加 target−x，因此最大可以添加到 ⌊target/2⌋
  // 如果个数还不够 n 个，就继续从 target,target+1,target+2,...依次添加。
  // 由于添加的数字是连续的，所以可以用等差数列求和公式快速求解。

  int minimumPossibleSum(int n, int target)
  {
    const int mod = 1e9 + 7;
    int m = target / 2;
    if (n <= m)
    {
      return (long long) (1 + n) * n / 2 % mod;
    }
    return ((long long) (1 + m) * m / 2 +
            ((long long) target + target + (n - m) - 1) * (n - m) / 2) %
           mod;
  }
};
