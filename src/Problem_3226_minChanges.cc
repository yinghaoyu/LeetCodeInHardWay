#include <vector>

using namespace std;

class Solution
{
 public:
  int minChanges(int n, int k)
  {
    // 根据题意，二进制 k 必须是 n 的子集
    // 所以在 n | k = n 的前提下，计算 n 和 k 之前的位差异即可
    return (n & k) != k ? -1 : __builtin_popcount(n ^ k);
  }
};
