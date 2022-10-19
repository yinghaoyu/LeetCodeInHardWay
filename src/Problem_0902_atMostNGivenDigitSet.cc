#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

// dp[i][0]=m+dp[i−1][0]×m+dp[i−1][1]×C[i]

// 其实重点要理解这个公式的推导过程 就像题解一中对dp的定义

// dp[i][0]表示由digits构成且小于n的前i位的数字的个数
// dp[i][1]表示由digits构成且等于n的前i位数字的个数

//那么对于公式中的各个部分

// m 就是 dp[i][0] 中单个字符所组成的数量

// dp[i-1][0] × m ：dp[i-1][0]小于n的前i-1位的数字个数，第i位就可以是m个字符其中之一，所以乘以m

// dp[i−1][1]×C[i] :
// C[i] 表示数组digits中小于n的第i位数字的元素个数
// dp[i-1][1]等于n的前i-1位的数字个数
// 因为前边都相等了，所以这个后边的这一位必须小于n[i],那么所组成的字符串个数就是乘以C[i]

class Solution
{
 public:
  // 1 3 5 7
  // 误区：这题是排列问题，不是组合问题，取硬币问题，取1面值、3面值谁先谁后不影响结果
  // 取硬币从左到右，如果没取 1 那么后面结果只可能是 35 37 57
  // 但是这里根据结果，31 也符合

  // 数位dp
  int atMostNGivenDigitSet(vector<string> &digits, int n)
  {
    string s = to_string(n);
    int m = digits.size(), k = s.size();
    // 前 i 位按由高到低顺序
    // dp[i][1] 的取值只能为 0 或 1(存在不相等或连续相等）

    vector<vector<int>> dp(k + 1, vector<int>(2));
    dp[0][1] = 1;  // base case 前 0 位都相等
    // 从高到低遍历n的位数
    for (int i = 1; i <= k; i++)
    {
      // 从左往右遍历digits
      for (int j = 0; j < m; j++)
      {
        if (digits[j][0] == s[i - 1])  // s的第 i 个字符下标为 i - 1
        {
          // 如果当前值digit字符恰好等于s当前字符
          // 需要连续相等，dp[i][1]明显取决于dp[i-1][1]
          dp[i][1] = dp[i - 1][1];
        }
        else if (digits[j][0] < s[i - 1])
        {
          // dp[i-1]的数据分成了两部分，dp[i-1][1]并不包含在dp[i-1][0]中
          // 前 i-1 位相等，当前 i 位可以取digits[j][0] < s[i - 1]
          // dp[i][0] 分两种情况统计：
          // 情况一：
          // 如果当前值digit字符 < s当前字符 且 前 i - 1 个字符相等，此时算 1 次
          // 如果当前值digit字符 < s当前字符 且 前 i - 1 个字符不相等，此时算 0 次
          dp[i][0] += dp[i - 1][1];
        }
        else
        {
          // digits[j][0] > s[i - 1]
          // 不符合条件
          break;
        }
      }
      if (i > 1)  // 当i == 0 时，实际上不符合一下计算条件
      {
        // 前置条件：前 i - 1 位构成的数字 <= n
        // 情况二：
        // 前 i - 1 个字符不相等，那么第 i 位取digits的任意字符都可行(dp[i - 1][0] * m)
        // 前 i - 1 个字符不填，那么第 i 位取digits的任意字符都可行(m)
        dp[i][0] += m + dp[i - 1][0] * m;
      }
    }
    return dp[k][0] + dp[k][1];
  }
};

void testAtMostNGivenDigitSet()
{
  Solution s;
  vector<string> digits1 = {"1", "3", "5", "7"};
  vector<string> digits2 = {"1", "4", "9"};
  vector<string> digits3 = {"7"};

  EXPECT_EQ_INT(20, s.atMostNGivenDigitSet(digits1, 100));
  EXPECT_EQ_INT(29523, s.atMostNGivenDigitSet(digits2, 1000000000));
  EXPECT_EQ_INT(1, s.atMostNGivenDigitSet(digits3, 8));

  EXPECT_SUMMARY;
}

int main()
{
  testAtMostNGivenDigitSet();
  return 0;
}
