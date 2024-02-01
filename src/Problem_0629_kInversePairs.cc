#include <vector>

using namespace std;

// TODO: figure it out.
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
          for (int p = 0; p <= j; p++)
          {
            dp[i][j] = (dp[i][j] + dp[i - 1][p]) % mod;
          }
        }
        else
        {
          // i <= j
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
