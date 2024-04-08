#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV1gM41197rM/
// 多维背包问题，0 1 背包问题(0表示不要，1表示要)
class Solution
{
 private:
  static constexpr int mod = 1e9 + 7;

 public:
  // n : 员工的额度，不能超
  // p : 利润的额度，不能少
  // group[i] : i号项目需要几个人
  // profit[i] : i号项目产生的利润
  // 返回能做到员工不能超过n，利润不能少于p的计划有多少个
  int profitableSchemes1(int n, int minProfit, vector<int>& group, vector<int>& profit)
  {
    return f1(group, profit, 0, n, minProfit);
  }

  // i : 来到i号工作
  // r : 员工额度还有r人，如果r<=0说明已经没法再选择工作了
  // s : 利润还有s才能达标，如果s<=0说明之前的选择已经让利润达标了
  // 返回 : i.... r、s，有多少种方案
  int f1(vector<int>& g, vector<int>& p, int i, int r, int s)
  {
    if (r <= 0)
    {
      // 人已经耗尽了，之前可能选了一些工作
      return s <= 0 ? 1 : 0;
    }
    // r > 0
    if (i == g.size())
    {
      // 工作耗尽了，之前可能选了一些工作
      return s <= 0 ? 1 : 0;
    }
    // 不要当前工作
    int p1 = f1(g, p, i + 1, r, s);
    // 要做当前工作
    int p2 = 0;
    if (g[i] <= r)
    {
      p2 = f1(g, p, i + 1, r - g[i], s - p[i]);
    }
    return p1 + p2;
  }

  // 记忆化搜索
  int profitableSchemes2(int n, int minProfit, vector<int>& group, vector<int>& profit)
  {
    int m = group.size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, -1)));
    return f2(group, profit, 0, n, minProfit, dp);
  }

  int f2(vector<int>& g, vector<int>& p, int i, int r, int s, vector<vector<vector<int>>>& dp)
  {
    if (r <= 0)
    {
      return s == 0 ? 1 : 0;
    }
    if (i == g.size())
    {
      return s == 0 ? 1 : 0;
    }
    if (dp[i][r][s] != -1)
    {
      return dp[i][r][s];
    }
    int p1 = f2(g, p, i + 1, r, s, dp);
    int p2 = 0;
    if (g[i] <= r)
    {
      // 注意这里取利润为0，后面也会累加方法数，目的是让dp[i][r][s]在合法空间
      p2 = f2(g, p, i + 1, r - g[i], std::max(0, s - p[i]), dp);
    }
    int ans = (p1 + p2) % mod;
    dp[i][r][s] = ans;
    return ans;
  }

  // 动态规划 + 空间优化
  int profitableSchemes3(int n, int minProfit, vector<int>& group, vector<int>& profit)
  {
    // i = 没有工作的时候，i == g.length
    vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));
    for (int r = 0; r <= n; r++)
    {
      dp[r][0] = 1;
    }
    int m = group.size();
    for (int i = m - 1; i >= 0; i--)
    {
      for (int r = n; r >= 0; r--)
      {
        for (int s = minProfit; s >= 0; s--)
        {
          int p1 = dp[r][s];
          int p2 = group[i] <= r ? dp[r - group[i]][std::max(0, s - profit[i])] : 0;
          dp[r][s] = (p1 + p2) % mod;
        }
      }
    }
    return dp[n][minProfit];
  }
};
