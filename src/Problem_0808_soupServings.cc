#include <math.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 记忆化搜索
  double process(int restA, int restB, unordered_map<string, double> &visited)
  {
    if (restA <= 0 && restB <= 0)
    {
      // 同时倒完
      return 0.5;
    }
    if (restA <= 0)
    {
      // A先倒完
      return 1.0;
    }
    if (restB <= 0)
    {
      // B先倒完
      return 0.0;
    }
    string enc = std::to_string(restA) + " " + std::to_string(restB);
    if (visited.count(enc))
    {
      return visited[enc];
    }
    double p1 = process(restA - 100, restB, visited);
    double p2 = process(restA - 75, restB - 25, visited);
    double p3 = process(restA - 50, restB - 50, visited);
    double p4 = process(restA - 25, restB - 75, visited);
    visited[enc] = 0.25 * (p1 + p2 + p3 + p4);
    return visited[enc];
  }

  double soupServings1(int n)
  {
    if (n >= 5000)
    {
      // 误差已经小于1e-5
      // 这个参数可以根据输入3000 4000 5000 测试得出
      return 1.0;
    }
    unordered_map<string, double> visited;
    return process(n, n, visited);
  }

  // 记忆化搜索改dp
  double soupServings2(int n)
  {
    n = ceil((double) n / 25);
    if (n >= 200)
    {
      return 1.0;
    }
    vector<vector<double>> dp(n + 1, vector<double>(n + 1));
    // restA = 0, restB = 0
    dp[0][0] = 0.5;
    for (int i = 1; i <= n; i++)
    {
      // restA = 0, restB != 0
      dp[0][i] = 1.0;
    }
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        dp[i][j] =
            (dp[std::max(0, i - 4)][j] + dp[std::max(0, i - 3)][j - 1] + dp[std::max(0, i - 2)][std::max(0, j - 2)] + dp[i - 1][std::max(0, j - 3)]) * 0.25;
      }
    }
    return dp[n][n];
  }
};

void testSoupServings()
{
  Solution s;
  EXPECT_EQ_DOUBLE(0.62500, s.soupServings1(50));
  EXPECT_EQ_DOUBLE(0.71875, s.soupServings1(100));
  EXPECT_EQ_DOUBLE(0.97657, s.soupServings1(1000));
  EXPECT_EQ_DOUBLE(1.00000, s.soupServings1(10000));
  EXPECT_EQ_DOUBLE(1.00000, s.soupServings1(1000000000));
  EXPECT_EQ_DOUBLE(0.62500, s.soupServings2(50));
  EXPECT_EQ_DOUBLE(0.71875, s.soupServings2(100));
  EXPECT_EQ_DOUBLE(0.97657, s.soupServings2(1000));
  EXPECT_EQ_DOUBLE(1.00000, s.soupServings2(10000));
  EXPECT_EQ_DOUBLE(1.00000, s.soupServings2(1000000000));
  EXPECT_SUMMARY;
}

int main()
{
  testSoupServings();
  return 0;
}
