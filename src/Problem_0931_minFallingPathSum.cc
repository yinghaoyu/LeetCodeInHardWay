#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, INT32_MAX));
    for (int j = 0; j < m; j++)
    {
      dp[n - 1][j] = matrix[n - 1][j];
    }
    for (int i = n - 2; i >= 0; i--)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        dp[i][j] = dp[i + 1][j] + matrix[i][j];
        if (j - 1 >= 0)
        {
          dp[i][j] = std::min(dp[i][j], dp[i + 1][j - 1] + matrix[i][j]);
        }
        if (j + 1 < n)
        {
          dp[i][j] = std::min(dp[i][j], dp[i + 1][j + 1] + matrix[i][j]);
        }
      }
    }
    int ans = INT32_MAX;
    for (int j = 0; j < m; j++)
    {
      ans = std::min(ans, dp[0][j]);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> m1 = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
  vector<vector<int>> m2 = {{-19, 57}, {-40, -5}};
  EXPECT_EQ_INT(13, s.minFallingPathSum(m1));
  EXPECT_EQ_INT(-59, s.minFallingPathSum(m2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
