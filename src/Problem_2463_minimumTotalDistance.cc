#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 private:
  static constexpr long NA = LONG_MAX;

  static constexpr int MAXN = 101;

  static constexpr int MAXM = 101;

  int n, m;

  // 工厂下标从1开始，fac[i][0]表示位置，fac[i][1]表示容量
  int fac[MAXN][2];

  // 机器人下标从1开始，rob[i]表示位置
  int rob[MAXM];

  // dp[i][j] : 1...i工厂去修理1...j号机器人，最短总距离是多少
  long dp[MAXN][MAXM];

  // 前缀和数组
  long sum[MAXM];

  // 单调队列
  int queue[MAXM];

  int l, r;

  void build(vector<vector<int>>& factory, vector<int>& robot)
  {
    // 工厂和机器人都根据所在位置排序
    std::sort(factory.begin(), factory.end(),
              [](vector<int>& l, vector<int>& r) { return l[0] < r[0]; });
    std::sort(robot.begin(), robot.end());
    n = factory.size();
    m = robot.size();
    // 让工厂和机器人的下标都从1开始
    for (int i = 1; i <= n; i++)
    {
      fac[i][0] = factory[i - 1][0];
      fac[i][1] = factory[i - 1][1];
    }
    for (int i = 1; i <= m; i++)
    {
      rob[i] = robot.at(i - 1);
    }
    // dp初始化
    for (int j = 1; j <= m; j++)
    {
      dp[0][j] = NA;
    }
  }

  // 最优解O(n * m)

  // i号工厂和j号机器人的距离
  long dist(int i, int j) { return std::abs((long) fac[i][0] - rob[j]); }

  // i号工厂从j号机器人开始负责的指标
  // 真的可行，返回指标的值
  // 如果不可行，返回NA
  long value(int i, int j)
  {
    if (dp[i - 1][j - 1] == NA)
    {
      return NA;
    }
    return dp[i - 1][j - 1] - sum[j - 1];
  }

 public:
  // 其他题解都没有达到这个最优复杂度
  long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory)
  {
    build(factory, robot);
    for (int i = 1, cap; i <= n; i++)
    {
      // i号工厂的容量
      cap = fac[i][1];
      // sum[j]表示
      // 1号机器人去往i号工厂的距离
      // 2号机器人去往i号工厂的距离
      // ...
      // j号机器人去往i号工厂的距离
      // 上面全加起来，也就是前缀和的概念
      for (int j = 1; j <= m; j++)
      {
        sum[j] = sum[j - 1] + dist(i, j);
      }
      l = r = 0;
      for (int j = 1; j <= m; j++)
      {
        dp[i][j] = dp[i - 1][j];
        if (value(i, j) != NA)
        {
          while (l < r && value(i, queue[r - 1]) >= value(i, j))
          {
            r--;
          }
          queue[r++] = j;
        }
        if (l < r && queue[l] == j - cap)
        {
          l++;
        }
        if (l < r)
        {
          dp[i][j] = std::min(dp[i][j], value(i, queue[l]) + sum[j]);
        }
      }
    }
    return dp[n][m];
  }
};
