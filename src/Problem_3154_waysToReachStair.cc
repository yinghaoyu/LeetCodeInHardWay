#include <unordered_map>

using namespace std;

class Solution
{
 private:
  // 记忆化搜索
  unordered_map<long long, int> dp;

 public:
  int waysToReachStair(int k) { return f(1, 0, false, k); }

  // i 表示当前来到第 i 级台阶
  // j 表示操作2 用了 j 次
  // down 表示上次操作是否用了操作1
  // 返回方法数
  int f(int i, int j, bool down, int k)
  {
    if (i > k + 1)
    {
      // 由于操作1不能连续使用，无法到达终点1
      return 0;
    }
    // 状态压缩
    long long mask = (long long) i << 32 | j << 1 | down;
    if (dp.count(mask))
    {
      return dp[mask];
    }
    int ans = i == k;
    // 操作2
    ans += f(i + (1 << j), j + 1, false, k);
    if (i > 0 && !down)
    {
      // 操作1
      ans += f(i - 1, j, true, k);
    }
    dp[mask] = ans;
    return ans;
  }
};
