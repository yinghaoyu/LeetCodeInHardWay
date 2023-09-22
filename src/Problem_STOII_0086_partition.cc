#include <iostream>
#include <string>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/palindrome-partitioning/
// @sa Problem_0131_partition.cc

class Solution
{
 public:
  vector<vector<bool>> getDp(const string &s)
  {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n));
    for (int i = 0; i < n - 1; i++)
    {
      dp[i][i] = true;
      dp[i][i + 1] = s[i] == s[i + 1];
    }
    dp[n - 1][n - 1] = true;
    for (int i = 2; i < n; i++)
    {
      int left = 0;
      int right = i;
      while (left < n && right < n)
      {
        dp[left][right] = s[left] == s[right] && dp[left + 1][right - 1];
        left++;
        right++;
      }
    }
    return dp;
  }

  void process(const string &s, int index, vector<vector<bool>> &dp, vector<string> &path, vector<vector<string>> &ans)
  {
    if (index == s.length())
    {
      ans.push_back(path);
      return;
    }
    for (int i = index; i < s.length(); i++)
    {
      if (dp[index][i])
      {
        path.push_back(s.substr(index, i - index + 1));
        process(s, i + 1, dp, path, ans);
        path.pop_back();
      }
    }
  }

  vector<vector<string>> partition(string s)
  {
    vector<vector<bool>> dp = getDp(s);
    vector<string> path;
    vector<vector<string>> ans;
    process(s, 0, dp, path, ans);
    return ans;
  }
};
