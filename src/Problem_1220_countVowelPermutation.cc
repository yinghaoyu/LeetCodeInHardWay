#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV13k4y1D7Dn/
// 设 dp[m][n] 表示长度为m，必须以 n 字符结尾的合法串数量
// 根据题意，有
// dp[m][a] = dp[m-1][e] + dp[m-1][i]+ dp[m-1][u]
// dp[m][e] = dp[m-1][a] + dp[m-1][i]
// dp[m][i] = dp[m-1][e] + dp[m-1][o]
// dp[m][o] = dp[m-1][i]
// dp[m][u] = dp[m-1][i] + dp[m-1][o]

// 5 维 1 阶递推式
class Solution
{
 public:
  int countVowelPermutation(int n)
  {
    // 长度为1的时候，以a、e、i、o、u结尾的合法数量
    vector<vector<int>> start = {{1, 1, 1, 1, 1}};
    vector<vector<int>> base = {
        {0, 1, 0, 0, 0}, {1, 0, 1, 0, 0}, {1, 1, 0, 1, 1}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 0}};
    vector<vector<int>> ans = multiply(start, power(base, n - 1));
    int ret = 0;
    for (int a : ans[0])
    {
      ret = (ret + a) % MOD;
    }
    return ret;
  }

  static constexpr int MOD = 1000000007;

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
