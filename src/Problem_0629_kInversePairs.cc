#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV1pN41157uX/
class Solution
{
 public:
  // 最普通的动态规划
  // 不优化枚举
  int kInversePairs(int n, int k)
  {
    static const int mod = 1e9 + 7;
    // dp[i][j] : 1、2、3...i这些数字，形成的排列一定要有j个逆序对，请问这样的排列有几种
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
      dp[i][0] = 1;
      for (int j = 1; j <= k; j++)
      {
        if (i > j)
        {
          // 设 i = e
          // 假设 a b c d e 共 5 个数，依次从小到大，要形成 3 个逆序对
          // 考虑排列组合
          // 当 e 在最后位置，那么方法数有 dp[4][3]，e 这个数最大，前面都是小于 e 的数
          // 当 e 在 c 和 d 之间，那么方法数有 dp[4][2]，因为 e 和 d 已经是一对逆序对
          // ...
          // 当 e 在 a 和 b 之间，那么方法数有 dp[4][0]
          for (int p = 0; p <= j; p++)
          {
            dp[i][j] = (dp[i][j] + dp[i - 1][p]) % mod;
          }
        }
        else
        {
          // i <= j
          // 同理
          for (int p = j - i + 1; p <= j; p++)
          {
            dp[i][j] = (dp[i][j] + dp[i - 1][p]) % mod;
          }
        }
      }
    }
    return dp[n][k];
  }

  // 根据观察方法1优化枚举
  // 最优解
  // 其实可以进一步空间压缩
  int kInversePairs2(int n, int k)
  {
    static const int mod = 1e9 + 7;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    dp[0][0] = 1;
    // window : 窗口的累加和
    for (int i = 1, window; i <= n; i++)
    {
      dp[i][0] = 1;
      window = 1;
      for (int j = 1; j <= k; j++)
      {
        if (i > j)
        {
          window = (window + dp[i - 1][j]) % mod;
        }
        else
        {
          // i <= j
          window = ((window + dp[i - 1][j]) % mod - dp[i - 1][j - i] + mod) % mod;
        }
        dp[i][j] = window;
      }
    }
    return dp[n][k];
  }
};
