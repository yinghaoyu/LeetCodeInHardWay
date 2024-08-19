#include <vector>

using namespace std;

class Solution
{
 public:
  int checkRecord1(int n)
  {
    // dp[i][j][k] 表示前 i 天有 j 个 A 且结尾有连续 k 个 L 的可奖励的出勤记录的数量
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3)));
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
      // 以 P 为结尾的数量
      for (int j = 0; j <= 1; j++)
      {
        for (int k = 0; k <= 2; k++)
        {
          // 当前字符为 P ，那么会让连续的 L 清0
          dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][k]) % MOD;
        }
      }

      // 以 A 为结尾的数量
      for (int k = 0; k <= 2; k++)
      {
        // 当前的字符为 A ，按题设只能出现1次A
        dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][k]) % MOD;
      }

      // 以 L 为结尾的数量
      for (int j = 0; j <= 1; j++)
      {
        for (int k = 1; k <= 2; k++)
        {
          // 当前的字符为 L ，按题设会让 k 增加 1
          dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k - 1]) % MOD;
        }
      }
    }

    int ans = 0;
    for (int j = 0; j <= 1; j++)
    {
      for (int k = 0; k <= 2; k++)
      {
        // 这些学生都满足题设条件
        ans = (ans + dp[n][j][k]) % MOD;
      }
    }
    return ans;
  }

  // TODO: figure it out
  int checkRecord2(int n)
  {
    // 1天的情况下，各种状态的合法数量
    vector<vector<int>> start = {{1, 1, 0, 1, 0, 0}};
    vector<vector<int>> base = {{1, 1, 0, 1, 0, 0}, {1, 0, 1, 1, 0, 0}, {1, 0, 0, 1, 0, 0},
                                {0, 0, 0, 1, 1, 0}, {0, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 0}};
    vector<vector<int>> ans = multiply(start, power(base, n - 1));
    int ret = 0;
    for (int a : ans[0])
    {
      ret = (ret + a) % MOD;
    }
    return ret;
  }

  static constexpr int MOD = 1e9 + 7;

  // 矩阵相乘 + 乘法取模
  // a的列数一定要等于b的行数
  vector<vector<int>> multiply(vector<vector<int>>& a, vector<vector<int>> b)
  {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<int>> ans(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        for (int c = 0; c < k; c++)
        {
          ans[i][j] = (int) (((long) a[i][c] * b[c][j] + ans[i][j]) % MOD);
        }
      }
    }
    return ans;
  }

  // 矩阵快速幂
  vector<vector<int>> power(vector<vector<int>>& m, int p)
  {
    int n = m.size();
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
      ans[i][i] = 1;
    }
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)
      {
        ans = multiply(ans, m);
      }
      m = multiply(m, m);
    }
    return ans;
  }
};
