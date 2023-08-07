#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// seem as leetcode 0820
// https://leetcode-cn.com/problems/short-encoding-of-words/
// see at Problem_0820_minimumLengthEncoding.cc
class Solution
{
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

 public:
  int minimumLengthEncoding(vector<string> &words)
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
