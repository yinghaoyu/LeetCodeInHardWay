#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 数形 dp
class Solution
{
 public:
  // 参考 y总yxc 的模版
  int countDigitOne(int n)
  {
    if (n == 0)
    {
      return 0;
    }
    vector<int> nums;
    auto dp = getDp(n);
    while (n)
    {
      nums.push_back(n % 10);
      n /= 10;
    }
    int ans = 0;
    int last = 0;  // 记录上一位(虽然这里好像没啥用)
    int cnt = 0;   // 记录出现1的次数
    for (int i = nums.size() - 1; i >= 0; i--)
    {
      int x = nums[i];  // 从高位开始填
      if (cnt > 0)
      {
        // 如果前面有1出现，无法通过后面的数位加到，这里额外补充
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

  // 预处理
  vector<vector<int>> getDp(int n)
  {
    const int N = 10;
    const int M = 10;
    // dp[i][j]的含义为，第 i 位填 j 后的 1 的个数
    vector<vector<int>> dp(N, vector<int>(M));
    // 从第 1 位开始填
    for (int i = 1; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        for (int k = 0; k < M; k++)
        {
          dp[i][j] += dp[i - 1][k];
        }
        // 如果当前数为 1，那么所有低位，无论填什么都满足条件
        dp[i][j] += j == 1 ? pow(10, i - 1) : 0;
      }
    }
    return dp;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(6, s.countDigitOne(13));
  EXPECT_EQ_INT(0, s.countDigitOne(0));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
