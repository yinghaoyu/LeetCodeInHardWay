#include <algorithm>
#include <cmath>

using namespace std;

// TODO: figure it out.
class Solution
{
 private:
  constexpr static int MAXN = 5;
  constexpr static int MAXM = 5;
  constexpr static int MAXP = 7;
  constexpr static int MAXS = 3 * 3 * 3 * 3 * 3;  // std::pow(3, MAXM)

  int N;
  int M;
  int maxs;
  int dp[MAXN][MAXM][MAXS][MAXP][MAXP];

 public:
  int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount)
  {
    N = std::max(m, n);
    M = std::min(m, n);
    maxs = std::pow(3, M);
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        for (int s = 0; s < maxs; s++)
        {
          for (int a = 0; a <= introvertsCount; a++)
          {
            for (int b = 0; b <= extrovertsCount; b++)
            {
              dp[i][j][s][a][b] = -1;
            }
          }
        }
      }
    }
    return f(0, 0, 0, introvertsCount, extrovertsCount, 1);
  }

  // 当前来到i行j列的格子
  // s表示轮廓线的状态，可以得到左侧格子放了什么人，上侧格子放了什么人
  // 内向的人还有a个，外向的人还有b个
  // 返回最大的幸福感
  // 注意 : bit等于3的j次方，bit不是关键可变参数，因为bit的值被j的值决定
  int f(int i, int j, int s, int a, int b, int bit)
  {
    if (i == N)
    {
      return 0;
    }
    if (j == M)
    {
      return f(i + 1, 0, s, a, b, 1);
    }
    if (dp[i][j][s][a][b] != -1)
    {
      return dp[i][j][s][a][b];
    }
    // 当前格子不安置人
    int ans = f(i, j + 1, set(s, bit, 0), a, b, bit * 3);
    // 上方邻居的状态
    int up = get(s, bit);
    // 左方邻居的状态
    int left = j == 0 ? 0 : get(s, bit / 3);
    // 邻居人数
    int neighbor = 0;
    // 如果放置人，之前得到的幸福感要如何变化
    int pre = 0;
    if (up != 0)
    {
      neighbor++;
      // 上邻居是内向的人，幸福感要减30；是外向的人，幸福感要加20
      pre += up == 1 ? -30 : 20;
    }
    if (left != 0)
    {
      neighbor++;
      // 左邻居是内向的人，幸福感要减30；是外向的人，幸福感要加20
      pre += left == 1 ? -30 : 20;
    }
    if (a > 0)
    {
      // 当前格子决定放内向的人
      ans =
          std::max(ans, pre + 120 - neighbor * 30 + f(i, j + 1, set(s, bit, 1), a - 1, b, bit * 3));
    }
    if (b > 0)
    {
      // 当前格子决定放外向的人
      ans =
          std::max(ans, pre + 40 + neighbor * 20 + f(i, j + 1, set(s, bit, 2), a, b - 1, bit * 3));
    }
    dp[i][j][s][a][b] = ans;
    return ans;
  }

  // s表示当前状态，按照3进制来理解
  // 当前来到第j号格，3的j次方是bit
  // 返回s第j号格的值
  int get(int s, int bit) { return s / bit % 3; }

  // s表示当前状态，按照3进制来理解
  // 当前来到第j号格，3的j次方是bit
  // 把s第j号格的值设置成v，返回新状态
  int set(int s, int bit, int v) { return s - get(s, bit) * bit + v * bit; }
};
