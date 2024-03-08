#include <vector>

using namespace std;

class Solution
{
 public:
  // TODO: bfs dfs

  // 并查集
  int findCircleNum(vector<vector<int>>& isConnected)
  {
    int n = isConnected.size();
    UnionFind uf(n);
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (isConnected[i][j])
        {
          uf.unions(i, j);
        }
      }
    }
    return uf.size();
  }

  class UnionFind
  {
    vector<int> parent;
    vector<int> sizes;
    vector<int> help;
    int number;

   public:
    UnionFind(int n)
    {
      parent.resize(n);
      sizes.resize(n, 1);
      help.resize(n);
      for (int i = 0; i < n; i++)
      {
        parent[i] = i;
      }
      number = n;
    }

    int size() { return number; }

    int find(int i)
    {
      int hi = 0;
      while (i != parent[i])
      {
        help[hi++] = i;
        i = parent[i];
      }
      for (hi--; hi >= 0; hi--)
      {
        parent[help[hi]] = i;
      }
      return i;
    }

    void unions(int i, int j)
    {
      int fi = find(i);
      int fj = find(j);
      if (fi != fj)
      {
        if (sizes[fi] >= sizes[fj])
        {
          parent[fj] = fi;
          sizes[fi] += sizes[fj];
        }
        else
        {
          parent[fi] = fj;
          sizes[fj] += sizes[fi];
        }
        number--;
      }
    }
  };
};
