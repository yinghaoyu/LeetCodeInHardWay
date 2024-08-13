#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  // 最优解
  int superEggDrop1(int k, int n)
  {
    if (k == 1)
    {
      return n;
    }
    vector<vector<int>> dp(k + 1, vector<int>(n + 1));
    for (int j = 1; j <= n; j++)
    {
      for (int i = 1; i <= k; i++)
      {
        dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
        if (dp[i][j] >= n)
        {
          return j;
        }
      }
    }
    return -1;
  }

  // 最优解空间压缩
  int superEggDrop2(int k, int n)
  {
    if (k == 1)
    {
      return n;
    }
    vector<int> dp(k + 1);
    for (int j = 1; j <= n; j++)
    {
      int pre = 0;
      for (int i = 1; i <= k; i++)
      {
        int tmp = dp[i];
        dp[i] = dp[i] + pre + 1;
        pre = tmp;
        if (dp[i] >= n)
        {
          return j;
        }
      }
    }
    return -1;
  }
};
