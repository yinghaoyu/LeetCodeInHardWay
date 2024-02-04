#include <vector>

using namespace std;

class Solution
{
 public:
  int checkRecord(int n)
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
