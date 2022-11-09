#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int orderOfLargestPlusSign(int n, vector<vector<int>> &mines)
  {
    int ans = 0;
    unordered_set<int> zero;
    for (int i = 0; i < mines.size(); i++)
    {
      zero.emplace(mines[i][0] * n + mines[i][1]);
    }
    vector<vector<int>> dp(n, vector<int>(n, INT32_MAX));
    for (int i = 0; i < n; i++)
    {
      // left
      int count = 0;
      for (int j = 0; j < n; j++)
      {
        count += !zero.count(i * n + j) ? 1 : -count;
        dp[i][j] = std::min(dp[i][j], count);
      }
      // right
      count = 0;
      for (int j = n - 1; j >= 0; j--)
      {
        count += !zero.count(i * n + j) ? 1 : -count;
        dp[i][j] = std::min(dp[i][j], count);
      }
    }
    for (int i = 0; i < n; i++)
    {
      int count = 0;
      // up
      for (int j = 0; j < n; j++)
      {
        count += !zero.count(j * n + i) ? 1 : -count;
        dp[j][i] = std::min(dp[j][i], count);
      }
      // down
      count = 0;
      for (int j = n - 1; j >= 0; j--)
      {
        count += !zero.count(j * n + i) ? 1 : -count;
        dp[j][i] = std::min(dp[j][i], count);
        ans = std::max(ans, dp[j][i]);
      }
    }
    return ans;
  }
};

void testOrderOfLargestPlusSign()
{
  Solution s;
  vector<vector<int>> n1 = {{4, 2}};
  vector<vector<int>> n2 = {{0, 0}};
  vector<vector<int>> n3 = {{0, 1}, {0, 2}, {1, 0}, {1, 2}, {1, 4}, {2, 0}, {2, 2}, {3, 0}, {3, 1}, {4, 0}, {4, 1}, {4, 3}, {4, 4}};
  vector<vector<int>> n4 = {{3, 0}, {3, 3}};
  EXPECT_EQ_INT(2, s.orderOfLargestPlusSign(5, n1));
  EXPECT_EQ_INT(0, s.orderOfLargestPlusSign(1, n2));
  EXPECT_EQ_INT(1, s.orderOfLargestPlusSign(5, n3));
  EXPECT_EQ_INT(1, s.orderOfLargestPlusSign(5, n3));
  EXPECT_EQ_INT(3, s.orderOfLargestPlusSign(5, n4));
  EXPECT_SUMMARY;
}

int main()
{
  testOrderOfLargestPlusSign();
  return 0;
}
