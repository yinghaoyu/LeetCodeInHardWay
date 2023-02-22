#include <functional>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int process1(int n, int index, int m, vector<int> &sum)
  {
    if (index + 2 * m >= n)
    {
      // 一次性拿玩，这样对手就没有石头可拿
      return sum[index];
    }
    int min = INT32_MAX;
    for (int x = 1; x <= 2 * m; x++)
    {
      // 当前拿x堆，对手从i+x拿
      min = std::min(min, process1(n, index + x, max(x, m), sum));
    }

    // 对手拿最少，当前拿的就是最多
    return sum[index] - min;
  }
  // 递归
  int stoneGameII1(vector<int> &piles)
  {
    int n = piles.size();
    vector<int> sum(n + 1);
    for (int i = n - 1; i >= 0; i--)
    {
      // 预处理后缀数组
      sum[i] = sum[i + 1] + piles[i];
    }
    return process1(n, 0, 1, sum);
  }

  // 递归改记忆化搜索
  int stoneGameII2(vector<int> &piles)
  {
    int n = piles.size();
    vector<int> sum(n + 1);
    // M 的上界是多少？
    // 已知幂函数导数 > 0
    // 为了在 i 尽量小的情况下，使 M 尽量大，
    // 那么每次都拿满 2M 堆，最后有 (2+4+8+⋯+M)+2M<n
    vector<vector<int>> visited(n, vector<int>((n + 1) / 4 + 1));
    for (int i = n - 1; i >= 0; i--)
    {
      // 预处理后缀数组
      sum[i] = sum[i + 1] + piles[i];
    }
    return process2(n, 0, 1, sum, visited);
  }

  int process2(int n, int index, int m, vector<int> &sum, vector<vector<int>> &visited)
  {
    if (index + 2 * m >= n)
    {
      // 一次性拿玩，这样对手就没有石头可拿
      return sum[index];
    }
    if (visited[index][m])
    {
      return visited[index][m];
    }
    int min = INT32_MAX;
    for (int x = 1; x <= 2 * m; x++)
    {
      // 当前拿x堆，对手从i+x拿
      min = std::min(min, process2(n, index + x, max(x, m), sum, visited));
    }
    // 对手拿最少，当前拿的就是最多
    visited[index][m] = sum[index] - min;
    return visited[index][m];
  }

  int stoneGameII3(vector<int> &piles)
  {
    int sum = 0;
    int n = piles.size();
    vector<vector<int>> dp(n, vector<int>(n + 1));
    for (int i = n - 1; i >= 0; i--)
    {
      sum += piles[i];
      for (int m = i / 2 + 1; m >= 1; m--)
      {
        if (i + 2 * m >= n)
        {
          dp[i][m] = sum;
        }
        else
        {
          int min = INT32_MAX;
          for (int x = 1; x <= m * 2; x++)
          {
            min = std::min(min, dp[i + x][max(m, x)]);
          }
          dp[i][m] = sum - min;
        }
      }
    }
    return dp[0][1];
  }
};

void testStoneGameII()
{
  Solution s;
  vector<int> p1 = {2, 7, 9, 4, 4};
  vector<int> p2 = {1, 2, 3, 4, 5, 100};
  EXPECT_EQ_INT(10, s.stoneGameII1(p1));
  EXPECT_EQ_INT(104, s.stoneGameII1(p2));
  EXPECT_EQ_INT(10, s.stoneGameII2(p1));
  EXPECT_EQ_INT(104, s.stoneGameII2(p2));
  EXPECT_EQ_INT(10, s.stoneGameII3(p1));
  EXPECT_EQ_INT(104, s.stoneGameII3(p2));
  EXPECT_SUMMARY;
}

int main()
{
  testStoneGameII();
  return 0;
}
