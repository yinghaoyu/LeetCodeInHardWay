#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

// @sa https://leetcode.cn/problems/collect-coins-in-a-tree/solutions/2191371/tuo-bu-pai-xu-ji-lu-ru-dui-shi-jian-pyth-6uli

class Solution
{
 public:
  int collectTheCoins(vector<int> &coins, vector<vector<int>> &edges)
  {
    int n = coins.size();
    vector<vector<int>> g(n);
    vector<int> degree(n);
    for (auto &e : edges)
    {
      int x = e[0];
      int y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
      ++degree[x];
      ++degree[y];
    }
    int rest = n;
    {
      // 删除树中所有无金币的叶子节点，直到树中所有的叶子节点都是含有金币的
      queue<int> q;
      for (int i = 0; i < n; i++)
      {
        if (degree[i] == 1 && !coins[i])
        {
          q.push(i);
        }
      }
      while (!q.empty())
      {
        int cur = q.front();
        --degree[cur];
        q.pop();
        --rest;
        for (int next : g[cur])
        {
          --degree[next];
          if (degree[next] == 1 && !coins[next])
          {
            q.push(next);
          }
        }
      }
    }
    {
      // 由于可以「收集距离当前节点距离为 2 以内的所有金币」，
      // 我们没有必要移动到叶子节点再收集，而是移动到叶子节点的父节点的父节点，
      // 就能收集到叶子节点上的金币。
      for (int i = 0; i < 2; i++)
      {
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
          if (degree[i] == 1)
          {
            q.push(i);
          }
        }
        while (!q.empty())
        {
          int cur = q.front();
          --degree[cur];
          q.pop();
          --rest;
          for (int next : g[cur])
          {
            --degree[next];
          }
        }
      }
    }
    // 由于题目要求最后回到出发点，无论从哪个点出发，每条边都必须走两次。
    // 这是因为把出发点作为树根，递归遍历这棵树，那么往下「递」是一次，往上「归」又是一次，
    // 每条边都会经过两次。所以答案就是剩余边数乘 2。
    // 特别的，如果最后剩余的节点为1，或者为 0，是不需要走动的
    return rest == 0 ? 0 : (rest - 1) * 2;
  }
};

void test()
{
  Solution s;
  vector<int> c1 = {1, 0, 0, 0, 0, 1};
  vector<vector<int>> e1 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};
  vector<int> c2 = {0, 0, 0, 1, 1, 0, 0, 1};
  vector<vector<int>> e2 = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {5, 6}, {5, 7}};
  EXPECT_EQ_INT(2, s.collectTheCoins(c1, e1));
  EXPECT_EQ_INT(2, s.collectTheCoins(c2, e2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
