#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countDigitOne(int n)
  {
    if (n == 0)
    {
      return 0;
    }
    auto dp = getDp(n);
    vector<int> nums;
    while (n)
    {
      nums.push_back(n % 10);
      n /= 10;
    }
    int ans = 0;
    int last = 0;
    int cnt = 0;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
      int x = nums[i];
      if (cnt > 0)
      {
        ans += pow(10, i) * x * cnt;
      }
      for (int j = 0; j < x; j++)
      {
        ans += dp[i + 1][j];
      }
      last = x;
      if (x == 1)
      {
        cnt++;
      }
    }
    ans += cnt;
    return ans;
  }

  vector<vector<int>> getDp(int n)
  {
    const int N = 11;
    const int M = 10;
    vector<vector<int>> dp(N, vector<int>(M));
    for (int i = 1; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        for (int k = 0; k < M; k++)
        {
          dp[i][j] += dp[i - 1][k];
        }
        dp[i][j] += j == 1 ? pow(10, i - 1) : 0;
      }
    }
    return dp;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(5, s.countDigitOne(12));
  EXPECT_EQ_INT(6, s.countDigitOne(13));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
