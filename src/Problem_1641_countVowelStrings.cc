#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countVowelStrings1(int n)
  {
    // 1 <= n <= 50，因此只要取比n稍大的范围即可
    int N = 64;
    // 总共5个字符，用数字代替字母
    int M = 5;
    // dp[i][j]的含义为：
    // 总共有i个字符，以j为结尾的字符，符合字典序的有多少个
    vector<vector<int>> dp(N, vector<int>(M));
    for (int j = 0; j < M; j++)
    {
      // base case
      dp[1][j] = 1;
    }
    for (int i = 2; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        // 这里取 k <= j 满足字典序
        for (int k = 0; k <= j; k++)
        {
          dp[i][j] += dp[i - 1][k];
        }
      }
    }
    int ans = 0;
    for (int j = 0; j < M; j++)
    {
      ans += dp[n][j];
    }
    return ans;
  }

  // 排列组合
  // 对于题目要求长度为 n 的答案来说：
  //【如果 a e i o u 的数目确定，排序方式是唯一的】
  // 这样问题就转化成，一个长为 n 的字符串，划分成 5 段，能划分多少种
  // 由于每个元素都可能是 0 个，所以各个划分位置可以都在 n 的外面
  // C(n+4, 4)
  int countVowelStrings2(int n) { return (n + 4) * (n + 3) * (n + 2) * (n + 1) / 24; }
};

void testCountVowelStrings()
{
  Solution s;
  EXPECT_EQ_INT(5, s.countVowelStrings1(1));
  EXPECT_EQ_INT(15, s.countVowelStrings1(2));
  EXPECT_EQ_INT(66045, s.countVowelStrings1(33));
  EXPECT_EQ_INT(5, s.countVowelStrings2(1));
  EXPECT_EQ_INT(15, s.countVowelStrings2(2));
  EXPECT_EQ_INT(66045, s.countVowelStrings2(33));
  EXPECT_SUMMARY;
}

int main()
{
  testCountVowelStrings();
  return 0;
}
