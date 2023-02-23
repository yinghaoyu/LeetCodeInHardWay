#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int process(string &s, int index, unordered_set<string> &set)
  {
    if (index == s.length())
    {
      return 1;
    }
    int ways = 0;
    for (int end = index; end < s.length(); end++)
    {
      if (set.count(s.substr(index, end + 1 - index)))
      {
        ways += process(s, end + 1, set);
      }
    }
    return ways;
  }

  // 递归
  bool wordBreak1(string s, vector<string> &wordDict)
  {
    unordered_set<string> set(wordDict.begin(), wordDict.end());
    return process(s, 0, set) != 0;
  }

  // 递归改dp
  bool wordBreak2(string s, vector<string> &wordDict)
  {
    unordered_set<string> set(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int end = i; end < n; end++)
      {
        if (set.count(s.substr(i, end + 1 - i)))
        {
          dp[i] += dp[end + 1];
        }
      }
    }
    return dp[0] != 0;
  }

  class Node
  {
   public:
    bool end;
    unordered_map<int, Node *> nexts;

    Node() { end = false; }
  };

  // 字典树优化dp
  bool wordBreak3(string s, vector<string> &wordDict)
  {
    Node *root = new Node();
    for (string &str : wordDict)
    {
      Node *node = root;
      int index = 0;
      for (int i = 0; i < str.length(); i++)
      {
        index = str[i] - 'a';
        if (!node->nexts.count(index))
        {
          node->nexts[index] = new Node();
        }
        node = node->nexts[index];
      }
      node->end = true;
    }
    int N = s.length();
    vector<bool> dp(N + 1);
    dp[N] = true;
    for (int i = N - 1; i >= 0; i--)
    {
      Node *cur = root;
      for (int end = i; end < N; end++)
      {
        int path = s[end] - 'a';
        if (cur->nexts[path] == nullptr)
        {
          // 查询s[i..end]是否在字典树内
          break;
        }
        cur = cur->nexts[path];
        if (cur->end && dp[end + 1])
        {
          // 存在单词s[i..end]，并且end+1位置后面也能分割成单词
          dp[i] = true;
          break;
        }
      }
    }
    return dp[0];
  }
};

void testWordBreak()
{
  Solution s;
  vector<string> w1 = {"leet", "code"};
  vector<string> w2 = {"apple", "pen"};
  vector<string> w3 = {"cats", "dog", "sand", "and", "cat"};
  EXPECT_TRUE(s.wordBreak1("leetcode", w1));
  EXPECT_TRUE(s.wordBreak1("applepenapple", w2));
  EXPECT_FALSE(s.wordBreak1("catsandog", w3));
  EXPECT_TRUE(s.wordBreak2("leetcode", w1));
  EXPECT_TRUE(s.wordBreak2("applepenapple", w2));
  EXPECT_FALSE(s.wordBreak2("catsandog", w3));
  EXPECT_TRUE(s.wordBreak3("leetcode", w1));
  EXPECT_TRUE(s.wordBreak3("applepenapple", w2));
  EXPECT_FALSE(s.wordBreak3("catsandog", w3));
  EXPECT_SUMMARY;
}

int main()
{
  testWordBreak();
  return 0;
}
