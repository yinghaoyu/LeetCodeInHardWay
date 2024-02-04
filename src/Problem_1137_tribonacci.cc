#include <vector>

using namespace std;

class Solution
{
 public:
  int tribonacci(int n)
  {
    if (n == 0)
    {
      return 0;
    }
    if (n == 1)
    {
      return 1;
    }
    if (n == 2)
    {
      return 1;
    }
    vector<vector<long>> start = {{1, 1, 0}};
    vector<vector<long>> base = {{1, 1, 0}, {1, 0, 1}, {1, 0, 0}};
    vector<vector<long>> ans = multiply(start, power(base, n - 2));
    return ans[0][0];
  }

  // 矩阵相乘
  // a的列数一定要等于b的行数
  vector<vector<long>> multiply(vector<vector<long>>& a, vector<vector<long>> b)
  {
    int n = a.size();
    int m = b[0].size();
    int k = a[0].size();
    vector<vector<long>> ans(n, vector<long>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        for (int c = 0; c < k; c++)
        {
          ans[i][j] += a[i][c] * b[c][j];
        }
      }
    }
    return ans;
  }

  // 矩阵快速幂
  vector<vector<long>> power(vector<vector<long>>& m, int p)
  {
    int n = m.size();
    vector<vector<long>> ans(n, vector<long>(n));
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
