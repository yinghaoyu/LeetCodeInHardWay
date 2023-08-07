#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// seem as leetcode 0677
//  https://leetcode-cn.com/problems/map-sum-pairs/
//  see at Problem_0677_MapSum.cc
class MapSum
{
  class Node
  {
   public:
    int pass;
    int end;
    int val;
    unordered_map<int, Node *> nexts;
    Node()
    {
      pass = 0;
      end = 0;
      val = 0;
    }
  };

  Node *root;

 public:
  /** Initialize your data structure here. */
  MapSum() { root = new Node(); }

  void insert(string key, int val)
  {
    Node *cur = root;
    cur->pass++;
    for (auto &c : key)
    {
      if (!cur->nexts.count(c))
      {
        cur->nexts[c] = new Node();
      }
      cur = cur->nexts[c];
      cur->pass++;
    }
    cur->val = val;
    cur->end++;
  }

  int sum(string prefix)
  {
    Node *cur = root;
    for (auto &c : prefix)
    {
      if (!cur->nexts.count(c))
      {
        return 0;
      }
      cur = cur->nexts[c];
    }
    int ans = 0;
    function<void(Node *)> dfs = [&](Node *cur)
    {
      ans += cur->val;
      for (auto &[c, node] : cur->nexts)
      {
        dfs(node);
      }
    };
    dfs(cur);
    return ans;
  }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
