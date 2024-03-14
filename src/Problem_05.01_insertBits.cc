class Solution
{
 public:
  int insertBits(int N, int M, int i, int j)
  {
    int mask = 0;
    for (int k = i; k <= j; k++)
    {
      // 先拼 i...j 位全为 1 的 mask
      mask |= (1 << k);
    }
    // ~mask & N 使得 N 的 i...j 位全为 0
    // 再把 M 移动到 i 位上
    return (~mask & N) | (M << i);
  }
};
