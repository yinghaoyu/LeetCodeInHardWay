#include <string>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/similar-string-groups/
// @sa Problem_0839_numSimilarGroups.cc
class Solution
{
 public:
  int numSimilarGroups(vector<string>& strs)
  {
    int n = strs.size();
    int m = strs[0].length();
    UnionFind uf(n);
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        int diff = 0;
        for (int k = 0; k < m && diff < 3; k++)
        {
          if (strs[i][k] != strs[j][k])
          {
            diff++;
          }
        }
        if (diff == 0 || diff == 2)
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
