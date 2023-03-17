#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minDistance1(string word1, string word2) { return process(word1, word2, 1, 1, 1); }

  int minDistance2(string word1, string word2) { return dp(word1, word2, 1, 1, 1); }

  // s1转化成s2，有3种操作
  // 增加字符的代价为ic
  // 删除字符的代价为dc
  // 替换字符的代价为rc
  int dp(string& str1, string& str2, int ic, int dc, int rc)
  {
    int N = str1.length();
    int M = str2.length();
    vector<vector<int>> dp(N + 1, vector<int>(M + 1));
    // dp[i][j]的含义为取前缀长度i的str1，转换成前缀长度为j的str2，最小需要的代价
    // dp[0][0] = 0
    for (int i = 1; i <= N; i++)
    {
      // 长度为i的str1，转成长度为0的str2，只需要删除i个字符，最小代价为dc * i
      dp[i][0] = dc * i;
    }
    for (int j = 1; j <= M; j++)
    {
      // 长度为0的str1，转成长度为i的str2，只需要添加i个字符，最小代价为ic * i
      dp[0][j] = ic * j;
    }
    for (int i = 1; i <= N; i++)
    {
      for (int j = 1; j <= M; j++)
      {
        // 可能性一：str1第i个字符和str2的第j个字符相等，长度为i-1的str1，转成长度为j-1的str2的最小代价，然后对第i个字符保持不变
        // 可能性二：str1第i个字符和str2的第j个字符不相等，长度为i-1的str1，转成长度为j-1的str2的最小代价，然后对第i个字符替换
        // 可能性三：长度为i的str1，转成长度为j-1的str2，此时只需要插入一个字符，让str2长度由j-1变成j
        // 可能性四：长度为i-1的str1，就可以转成长度为j的str2，那么长度为i的str1多出来一个字符，删除就可以了
        dp[i][j] = dp[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : rc);
        dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + ic);
        dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + dc);
      }
    }
    return dp[N][M];
  }

  // 动态规划空间优化
  // TODO: figure it out
  int process(string &str1, string str2, int ic, int dc, int rc)
  {
    if (str1.length() == 0 || str2.length() == 0)
    {
      return 0;
    }
    string longs = str1.length() >= str2.length() ? str1 : str2;
    string shorts = longs == str2 ? str1 : str2;
    if (str1.length() < str2.length())
    {
      int tmp = ic;
      ic = dc;
      dc = tmp;
    }
    vector<int> dp(shorts.length() + 1);
    for (int i = 1; i <= shorts.length(); i++)
    {
      dp[i] = ic * i;
    }
    for (int i = 1; i <= longs.length(); i++)
    {
      int pre = dp[0];
      dp[0] = dc * i;
      for (int j = 1; j <= shorts.length(); j++)
      {
        int tmp = dp[j];
        if (longs[i - 1] == shorts[j - 1])
        {
          dp[j] = pre;
        }
        else
        {
          dp[j] = pre + rc;
        }
        dp[j] = std::min(dp[j], dp[j - 1] + ic);
        dp[j] = std::min(dp[j], tmp + dc);
        pre = tmp;
      }
    }
    return dp[shorts.length()];
  }
};

void testMinDistance()
{
  Solution s;
  EXPECT_EQ_INT(3, s.minDistance1("horse", "ros"));
  EXPECT_EQ_INT(5, s.minDistance1("intention", "execution"));
  EXPECT_EQ_INT(3, s.minDistance2("horse", "ros"));
  EXPECT_EQ_INT(5, s.minDistance2("intention", "execution"));
  EXPECT_SUMMARY;
}

int main()
{
  testMinDistance();
  return 0;
}
