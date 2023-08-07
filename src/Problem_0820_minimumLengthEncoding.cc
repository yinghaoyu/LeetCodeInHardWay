#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 存储后缀
  int minimumLengthEncoding1(vector<string> &words)
  {
    unordered_set<string> set(words.begin(), words.end());
    for (auto &word : words)
    {
      // 删除这个单词的所有后缀
      for (int i = 1; i < word.length(); i++)
      {
        set.erase(word.substr(i));
      }
    }
    int ans = 0;
    for (auto &word : set)
    {
      // 结果是每个单词的长度 + '#'字符的长度 1
      ans += word.length() + 1;
    }
    return ans;
  }

  class Tire
  {
   public:
    class Node
    {
     public:
      int pass;
      int end;
      unordered_map<int, Node *> nexts;
      Node()
      {
        pass = 0;
        end = 0;
      }
    };

    Node *root;

    Tire() { root = new Node(); }
  };

  int minimumLengthEncoding2(vector<string> &words)
  {
    Tire t;
    for (auto &word : words)
    {
      Tire::Node *cur = t.root;
      cur->pass++;
      for (int i = word.length() - 1; i >= 0; i--)
      {
        if (!cur->nexts.count(word[i]))
        {
          cur->nexts[word[i]] = new Tire::Node();
        }
        cur = cur->nexts[word[i]];
        cur->pass++;
      }
      cur->end++;
    }
    Tire::Node *cur = t.root;
    int ans = 0;
    function<void(Tire::Node *, int)> dfs = [&](Tire::Node *cur, int len)
    {
      if (cur->pass == cur->end)
      {
        // 叶子节点的 pass 和 end 相同
        ans += len + 1;
      }
      for (auto &[c, node] : cur->nexts)
      {
        dfs(node, len + 1);
      }
    };
    dfs(t.root, 0);
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> w1 = {"time", "me", "bell"};
  vector<string> w2 = {"t"};
  EXPECT_EQ_INT(10, s.minimumLengthEncoding1(w1));
  EXPECT_EQ_INT(2, s.minimumLengthEncoding1(w2));
  EXPECT_EQ_INT(10, s.minimumLengthEncoding2(w1));
  EXPECT_EQ_INT(2, s.minimumLengthEncoding2(w2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
