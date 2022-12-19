#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
  {
    unordered_map<int, vector<int>> g;
    for (auto &e : edges)
    {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    bool p1 = bfs(n, g, source, destination);
    vector<bool> seen(n);
    bool p2 = dfs(g, seen, source, destination);
    bool p3 = uf(n, edges, source, destination);
    return p1 | p2 | p3;
  }

  bool dfs(unordered_map<int, vector<int>> &g, vector<bool> &seen, int cur, int dest)
  {
    if (seen[cur])
    {
      return false;
    }
    if (cur == dest)
    {
      return true;
    }
    seen[cur] = true;
    for (auto &next : g[cur])
    {
      if (dfs(g,seen, next,dest))
      {
        return true;
      }
    }
    return false;
  }

  bool bfs(int n, unordered_map<int, vector<int>> &g, int source, int destination)
  {
    queue<int> q;
    vector<bool> seen(n);
    q.push(source);
    while (!q.empty())
    {
      int cur = q.front();
      q.pop();
      seen[cur] = true;
      if (cur == destination)
      {
        return true;
      }
      for (auto next : g[cur])
      {
        if (!seen[next])
        {
          q.push(next);
        }
      }
    }
    return false;
  }

  class UnionFind
  {
   public:
    vector<int> parents;
    vector<int> help;
    vector<int> size;
    int number;

   public:
    UnionFind(int n)
    {
      parents = vector<int>(n);
      std::iota(parents.begin(), parents.end(), 0);
      help = vector<int>(n);
      size = vector<int>(n, 1);
      number = n;
    }

    int find(int i)
    {
      int hi = 0;
      while (i != parents[i])
      {
        help[hi++] = i;
        i = parents[i];
      }
      for (hi--; hi >= 0; hi--)
      {
        parents[help[hi]] = i;
      }
      return i;
    }

    void unions(int i, int j)
    {
      int f1 = find(i);
      int f2 = find(j);
      if (f1 != f2)
      {
        if (size[f1] > size[f2])
        {
          size[f1] += size[f2];
          parents[f2] = f1;
        }
        else
        {
          size[f2] += size[f1];
          parents[f1] = f2;
        }
        number--;
      }
    }

    int num() { return number; }
  };

  // 并查集最优解
  bool uf(int n, vector<vector<int>> &edges, int source, int destination)
  {
    UnionFind uf(n);
    for (auto &e : edges)
    {
      uf.unions(e[0], e[1]);
    }
    return uf.find(source) == uf.find(destination);
  }
};

void testValidPath()
{
  Solution s;
  vector<vector<int>> e1 = {{0, 1}, {1, 2}, {2, 0}};
  vector<vector<int>> e2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
  EXPECT_TRUE(s.validPath(3, e1, 0, 2));
  EXPECT_FALSE(s.validPath(6, e2, 0, 5));
  EXPECT_SUMMARY;
}

int main()
{
  testValidPath();
  return 0;
}
