#include <string>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<vector<bool>> getdp(string &str)
  {
    int N = str.length();
    // dp[i][j]表示的含义为str[i..j]是否为回文串
    vector<vector<bool>> dp(N, vector<bool>(N));
    for (int i = 0; i < N - 1; i++)
    {
      // base case
      // 只有一个字符，当然是回文串
      dp[i][i] = true;
      // 有两个字符，相等就是回文串
      dp[i][i + 1] = str[i] == str[i + 1];
    }
    dp[N - 1][N - 1] = true;
    // 2个字符及以内，前面已经计算过，所以j从2开始
    for (int j = 2; j < N; j++)
    {
      int row = 0;
      int col = j;
      while (row < N && col < N)
      {
        // 当前位置字符相等，且区间内也是回文串，才满足回文串条件
        dp[row][col] = str[row] == str[col] && dp[row + 1][col - 1];
        row++;
        col++;
      }
    }
    return dp;
  }

  // s 字符串
  // s[0...index-1] 已经做过的决定，放入了path中
  // 在index开始做属于这个位置的决定，
  // index == s.len  path之前做的决定（一种分割方法），放进总答案ans里
  void process(string &s, int index, vector<string> &path, vector<vector<bool>> &dp, vector<vector<string>> &ans)
  {
    if (index == s.length())
    {
      ans.push_back(path);
    }
    else
    {
      for (int end = index; end < s.length(); end++)
      {
        // index..index
        // index..index+1
        // index..index+2
        // index..end
        if (dp[index][end])
        {
          // 只有s[index...end]是回文串，才往后尝试
          path.push_back(s.substr(index, end + 1 - index));
          process(s, end + 1, path, dp, ans);
          path.pop_back();
        }
      }
    }
  }

  vector<vector<string>> partition(string s)
  {
    // 动态规划预处理回文串
    vector<vector<bool>> dp = getdp(s);
    vector<string> path;
    vector<vector<string>> ans;
    process(s, 0, path, dp, ans);
    return ans;
  }
};

void testPartition()
{
  Solution s;
  vector<vector<string>> o1 = {{"a", "a", "b"}, {"aa", "b"}};
  vector<vector<string>> o2 = {{"a"}};
  EXPECT_TRUE(o1 == s.partition("aab"));
  EXPECT_TRUE(o2 == s.partition("a"));
  EXPECT_SUMMARY;
}

int main()
{
  testPartition();
  return 0;
}
