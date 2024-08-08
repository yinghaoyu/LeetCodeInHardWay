#include <cmath>

using namespace std;

// TODO: figure it out.
class Solution
{
 private:
  constexpr static int MAXN = 1001;
  constexpr static int MAXM = 5;
  constexpr static int MAXS = 3 * 3 * 3 * 3 * 3;  // std::pow(3, MAXM)
  constexpr static int MOD = 1e9 + 7;

  int N;
  int M;
  int maxs;
  int dp[MAXN][MAXM][MAXS];
  int first[MAXS];
  int size;

 public:
  int colorTheGrid(int m, int n)
  {
    build(m, n);
    int ans = 0;
    for (int i = 0; i < size; i++)
    {
      ans = (ans + f(1, 0, first[i], 1)) % MOD;
    }
    return ans;
  }

  void build(int rows, int cols)
  {
    N = std::max(rows, cols);
    M = std::min(rows, cols);
    maxs = (int) std::pow(3, M);
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        for (int s = 0; s < maxs; s++)
        {
          dp[i][j][s] = -1;
        }
      }
    }
    size = 0;
    dfs(0, 0, 1);
  }

  // 取得所有第一行的有效状态
  void dfs(int j, int s, int bit)
  {
    if (j == M)
    {
      first[size++] = s;
    }
    else
    {
      int left = j == 0 ? -1 : get(s, bit / 3);
      if (left != 0)
      {
        dfs(j + 1, set(s, bit, 0), bit * 3);
      }
      if (left != 1)
      {
        dfs(j + 1, set(s, bit, 1), bit * 3);
      }
      if (left != 2)
      {
        dfs(j + 1, set(s, bit, 2), bit * 3);
      }
    }
  }

  int f(int i, int j, int s, int bit)
  {
    if (i == N)
    {
      return 1;
    }
    if (j == M)
    {
      return f(i + 1, 0, s, 1);
    }
    if (dp[i][j][s] != -1)
    {
      return dp[i][j][s];
    }
    // 上方的颜色
    int up = get(s, bit);
    // 左侧的颜色，-1代表左侧没有格子
    int left = j == 0 ? -1 : get(s, bit / 3);
    int ans = 0;
    if (up != 0 && left != 0)
    {
      ans = (ans + f(i, j + 1, set(s, bit, 0), bit * 3)) % MOD;
    }
    if (up != 1 && left != 1)
    {
      ans = (ans + f(i, j + 1, set(s, bit, 1), bit * 3)) % MOD;
    }
    if (up != 2 && left != 2)
    {
      ans = (ans + f(i, j + 1, set(s, bit, 2), bit * 3)) % MOD;
    }
    dp[i][j][s] = ans;
    return ans;
  }

  int get(int s, int bit) { return s / bit % 3; }

  int set(int s, int bit, int v) { return s - get(s, bit) * bit + v * bit; }
};
