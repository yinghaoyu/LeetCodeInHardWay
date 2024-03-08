#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> findRedundantConnection(vector<vector<int>>& edges)
  {
    int n = edges.size();
    UnionFind uf(n + 1);
    for (auto& edge : edges)
    {
      if (uf.find(edge[0]) == uf.find(edge[1]))
      {
        return edge;
      }
      uf.unions(edge[0], edge[1]);
    }
    return {};
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
