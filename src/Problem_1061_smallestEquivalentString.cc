#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 并查集
  string smallestEquivalentString(string s1, string s2, string baseStr)
  {
    int n = s1.length();
    UnionFind uf(256);
    string ans;
    for (int i = 0; i < n; i++)
    {
      uf.unions(s1[i], s2[i]);
    }
    for (char c : baseStr)
    {
      ans.push_back(uf.find(c));
    }
    return ans;
  }

 private:
  class UnionFind
  {
   private:
    vector<int> father;
    vector<int> sizes;
    vector<int> help;
    int num;

   public:
    UnionFind(int n)
    {
      father.resize(n);
      sizes.resize(n, 1);
      help.resize(n);
      num = n;
      for (int i = 0; i < n; i++)
      {
        father[i] = i;
      }
    }

    int find(int i)
    {
      int hi = 0;
      while (i != father[i])
      {
        help[hi++] = i;
        i = father[i];
      }
      for (hi--; hi >= 0; hi--)
      {
        father[help[hi]] = i;
      }
      return i;
    }

    void unions(int i, int j)
    {
      int fi = find(i);
      int fj = find(j);
      if (fi != fj)
      {
        if (fi < fj)
        {
          // 谁字典序小，谁当父亲
          father[fj] = fi;
          sizes[fi] += sizes[fj];
        }
        else
        {
          father[fi] = fj;
          sizes[fj] += sizes[fi];
        }
        num--;
      }
    }
  };
};
