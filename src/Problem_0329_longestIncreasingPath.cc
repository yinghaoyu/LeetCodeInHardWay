#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int longestIncreasingPath(vector<vector<int>>& matrix)
  {
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      return 0;
    }
    int ans = 0;
    int N = matrix.size();
    int M = matrix[0].size();
    vector<vector<int>> dp(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        ans = std::max(ans, lip(matrix, i, j, dp));
      }
    }
    return ans;
  }

  int lip(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& dp)
  {
    if (dp[i][j] != 0)
    {
      return dp[i][j];
    }
    int next = 0;
    if (canWalk(matrix, i, j, i - 1, j))
    {
      next = std::max(next, lip(matrix, i - 1, j, dp));
    }
    if (canWalk(matrix, i, j, i + 1, j))
    {
      next = std::max(next, lip(matrix, i + 1, j, dp));
    }
    if (canWalk(matrix, i, j, i, j - 1))
    {
      next = std::max(next, lip(matrix, i, j - 1, dp));
    }
    if (canWalk(matrix, i, j, i, j + 1))
    {
      next = std::max(next, lip(matrix, i, j + 1, dp));
    }
    dp[i][j] = 1 + next;
    return dp[i][j];
  }

  bool canWalk(vector<vector<int>>& matrix, int i1, int j1, int i2, int j2)
  {
    return i2 >= 0 && i2 < matrix.size() && j2 >= 0 && j2 < matrix[0].size() &&
           matrix[i1][j1] < matrix[i2][j2];
  }
};

void testLongestIncreasingPath()
{
  Solution s;
  vector<vector<int>> m1 = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
  vector<vector<int>> m2 = {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}};
  vector<vector<int>> m3 = {{1}};
  EXPECT_EQ_INT(4, s.longestIncreasingPath(m1));
  EXPECT_EQ_INT(4, s.longestIncreasingPath(m2));
  EXPECT_EQ_INT(1, s.longestIncreasingPath(m3));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestIncreasingPath();
  return 0;
}
