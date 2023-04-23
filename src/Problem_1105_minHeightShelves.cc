#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
  {
    int n = books.size();
    // dp[i] 表示放下前 i 本书所用的最小高度
    vector<int> dp(n + 1, 1000000);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
      int maxHeight = 0;
      int curWidth = 0;
      for (int j = i; j >= 0; j--)
      {
        curWidth += books[j][0];
        if (curWidth > shelfWidth)
        {
          break;
        }
        maxHeight = std::max(maxHeight, books[j][1]);
        // 假定前 j 本书已经放在了书架上
        dp[i + 1] = std::min(dp[i + 1], dp[j] + maxHeight);
      }
    }
    return dp[n];
  }
};

void testMinHeightShelves()
{
  Solution s;
  vector<vector<int>> b1 = {{1, 1}, {2, 3}, {2, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 2}};
  vector<vector<int>> b2 = {{1, 3}, {2, 4}, {3, 2}};
  EXPECT_EQ_INT(6, s.minHeightShelves(b1, 4));
  EXPECT_EQ_INT(4, s.minHeightShelves(b2, 6));
  EXPECT_SUMMARY;
}

int main()
{
  testMinHeightShelves();

  return 0;
}
