#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV13k4y1D7Dn/
class Solution
{
 public:
  // 暴力方法
  // 为了找规律
  // 如果h==0，返回2*n的区域铺满的方法数
  // 如果h==1，返回1 + 2*n的区域铺满的方法数
  int f(int n, int h)
  {
    if (n == 0)
    {
      // 当 n == 0 且 h == 0 时，说明铺满了，返回一种方法数
      // 当 n == 0 但 h == 1 时，说明有 1 小块剩余（既不满足多米诺，也不满足托米诺），此方法不合法
      return h == 0 ? 1 : 0;
    }
    if (n == 1)
    {
      // 只能多米诺
      return 1;
    }
    // n >= 2
    if (h == 1)
    {
      // 有多余的小块，分两种情况
      // 如果给多出的小块上放托米诺，那么后续 n-1 是多米诺型的，即 f(n - 1, 0)
      // 如果给多出的小块上放多米诺，那么后续 n-1 是托米诺型的，即 f(n - 1, 1)
      return f(n - 1, 0) + f(n - 1, 1);
    }
    else
    {
      // 没有多余的小块，分三种情况
      // 竖着放多米诺，那么后续是多米诺型的，即 f(n - 1, 0)
      // 横着放两块多米诺，那么后续是多米诺型的，即 f(n - 2, 0)
      // 放一块托米诺，那么后续是托米诺型的，考虑两个方向即 2 * f(n - 2, 1)
      return f(n - 1, 0) + f(n - 2, 0) + 2 * f(n - 2, 1);
    }
  }

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
