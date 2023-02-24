#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void process(string &s, int index, string &path, vector<string> &ans, unordered_set<string> &set)
  {
    if (index == s.length())
    {
      ans.push_back(path.substr(1));
      return;
    }
    for (int end = index; end < s.length(); end++)
    {
      string cur = s.substr(index, end + 1 - index);
      if (set.count(cur))
      {
        path.append(" " + cur);
        process(s, end + 1, path, ans, set);
        path.erase(path.find_last_of(' '));
      }
    }
  }

  // 递归解
  vector<string> wordBreak1(string s, vector<string> &wordDict)
  {
    unordered_set<string> set(wordDict.begin(), wordDict.end());
    vector<string> ans;
    string path;
    process(s, 0, path, ans, set);
    return ans;
  }

  class Node
  {
   public:
    string path;
    bool end;
    unordered_map<int, Node *> nexts;

    Node()
    {
      end = false;
    }
  };

  vector<string> wordBreak2(string s, vector<string> &wordDict)
  {
    Node *root = gettrie(wordDict);
    vector<bool> dp = getdp(s, root);
    vector<string> path;
    vector<string> ans;
    process(s, 0, root, dp, path, ans);
    return ans;
  }

  void process(string &str, int index, Node *root, vector<bool> &dp, vector<string> &path, vector<string> &ans)
  {
    if (index == str.length())
    {
      string cur;
      for (int i = 0; i < path.size() - 1; i++)
      {
        cur.append(path.at(i) + " ");
      }
      cur.append(path.back());
      ans.push_back(cur);
    }
    else
    {
      Node *cur = root;
      for (int end = index; end < str.length(); end++)
      {
        int road = str[end] - 'a';
        if (!cur->nexts.count(road))
        {
          break;
        }
        cur = cur->nexts[road];
        if (cur->end && dp[end + 1])
        {
          path.push_back(cur->path);
          process(str, end + 1, root, dp, path, ans);
          path.pop_back();
        }
      }
    }
  }

  Node *gettrie(vector<string> &wordDict)
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
      node->path = str;
      node->end = true;
    }
    return root;
  }

  vector<bool> getdp(string &str, Node *root)
  {
    int N = str.length();
    vector<bool> dp(N + 1);
    dp[N] = true;
    for (int i = N - 1; i >= 0; i--)
    {
      Node *cur = root;
      for (int end = i; end < N; end++)
      {
        int path = str[end] - 'a';
        if (!cur->nexts.count(path))
        {
          break;
        }
        cur = cur->nexts[path];
        if (cur->end && dp[end + 1])
        {
          dp[i] = true;
          break;
        }
      }
    }
    return dp;
  }
};

bool isVectorEqual(vector<string> a, vector<string> b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

void testWordBreak()
{
  Solution s;
  vector<string> w1 = {"cat", "cats", "and", "sand", "dog"};
  vector<string> o1 = {"cats and dog", "cat sand dog"};
  vector<string> w2 = {"apple", "pen", "applepen", "pine", "pineapple"};
  vector<string> o2 = {"pine apple pen apple", "pineapple pen apple", "pine applepen apple"};
  vector<string> w3 = {"cats", "dog", "sand", "and", "cat"};
  vector<string> o3;
  EXPECT_TRUE(isVectorEqual(o1, s.wordBreak1("catsanddog", w1)));
  EXPECT_TRUE(isVectorEqual(o2, s.wordBreak1("pineapplepenapple", w2)));
  EXPECT_TRUE(isVectorEqual(o3, s.wordBreak1("catsandog", w3)));
  EXPECT_TRUE(isVectorEqual(o1, s.wordBreak2("catsanddog", w1)));
  EXPECT_TRUE(isVectorEqual(o2, s.wordBreak2("pineapplepenapple", w2)));
  EXPECT_TRUE(isVectorEqual(o3, s.wordBreak2("catsandog", w3)));
  EXPECT_SUMMARY;
}

int main()
{
  testWordBreak();
  return 0;
}
