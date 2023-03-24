#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 1.首先对于每一次操作的结果有两种情况.
  // 情况1: 在上一次操作的结果后面打印1个A. 即 dp[i] = dp[i - 1] + 1;
  // 情况2: 利用ctrl-v
  //
  // 我们假设dp[j]为复制的A的数量
  // 首先我们可以让j从1开始, 因为0的时候屏幕没有A, 无意义.
  // j最大为i - 3. 因为i使用ctrl-v, i - 1使用ctrl-c, i - 2使用ctrl-a, 而ctrl-a复制的A的数量为dp[i - 3]的A的数量
  // 即(int j = 1; j < i - 2; j++)
  //
  // 那么如果复制dp[j]这个数值x次, 总共可以复制的次数为i - (j + 2)次.
  //
  // 结果就等于dp[j]原有的A的个数 + 复制的次数 * dp[j]
  //
  // dp[j] + dp[j] * (i - j - 2)) = dp[j] * (i - j - 1);
  //
  // 时间复杂度O(N ^ 2)
  // 空间复杂度O(N)
  int maxA(int n)
  {
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
      // 按 A
      dp[i] = dp[i - 1] + 1;
      for (int j = 1; j < i - 2; j++)
      {
        dp[i] = std::max(dp[i], dp[j] * (i - j - 1));
      }
    }

    return dp[n];
  }
};

void testMaxA()
{
  Solution s;
  EXPECT_EQ_INT(3, s.maxA(3));
  EXPECT_EQ_INT(9, s.maxA(7));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxA();
  return 0;
}
