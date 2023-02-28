#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class UnionFind
  {
   private:
    vector<int> parents;
    vector<int> help;
    vector<int> size;
    int number;
    int m;

    int index(int i, int j) { return i * m + j; }

   public:
    UnionFind(vector<vector<char>> &grid)
    {
      number = 0;
      int n = grid.size();
      m = grid[0].size();
      int len = m * n;
      parents = vector<int>(len);
      help = vector<int>(len);
      size = vector<int>(len);
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          if (grid[i][j] == '1')
          {
            int idx = index(i, j);
            parents[idx] = idx;
            size[idx] = 1;
            number++;
          }
        }
      }
    }

    int find(int i)
    {
      int hi = 0;
      while (parents[i] != i)
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

    void unions(int r1, int c1, int r2, int c2)
    {
      int i = index(r1, c1);
      int j = index(r2, c2);
      int pi = find(i);
      int pj = find(j);
      if (pi != pj)
      {
        if (size[pi] < size[pj])
        {
          parents[pi] = pj;
          size[pj] += size[pi];
        }
        else
        {
          parents[pj] = pi;
          size[pi] += size[pj];
        }
        number--;
      }
    }

    int num() { return number; }
  };

 public:
  int numIslands1(vector<vector<char>> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    UnionFind uf(grid);
    for (int i = 1; i < n; i++)
    {
      if (grid[i][0] == '1' && grid[i - 1][0] == '1')
      {
        uf.unions(i, 0, i - 1, 0);
      }
    }
    for (int j = 1; j < m; j++)
    {
      if (grid[0][j] == '1' && grid[0][j - 1] == '1')
      {
        uf.unions(0, j, 0, j - 1);
      }
    }
    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j < m; j++)
      {
        if (grid[i][j] == '1')
        {
          if (grid[i - 1][j] == '1')
          {
            uf.unions(i, j, i - 1, j);
          }
          if (grid[i][j - 1] == '1')
          {
            uf.unions(i, j, i, j - 1);
          }
        }
      }
    }
    return uf.num();
  }

  int numIslands2(vector<vector<char>> &grid)
  {
    if (grid.size() == 0 || grid[0].size() == 0)
    {
      return 0;
    }
    int ans = 0;
    int n = grid.size();
    int m = grid[0].size();
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == '1')
        {
          ans++;
          infect(grid, i, j, n, m);
        }
      }
    }
    return ans;
  }

  void infect(vector<vector<char>> &grid, int i, int j, int n, int m)
  {
    if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != '1')
    {
      return;
    }
    grid[i][j] = '2';
    infect(grid, i + 1, j, n, m);
    infect(grid, i - 1, j, n, m);
    infect(grid, i, j + 1, n, m);
    infect(grid, i, j - 1, n, m);
  }
};

void testNumIslands()
{
  Solution s;
  vector<vector<char>> g1 = {{'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '0', '0', '0'}};
  vector<vector<char>> g2 = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};

  EXPECT_EQ_INT(1, s.numIslands1(g1));
  EXPECT_EQ_INT(3, s.numIslands1(g2));
  EXPECT_EQ_INT(1, s.numIslands2(g1));
  EXPECT_EQ_INT(3, s.numIslands2(g2));
  EXPECT_SUMMARY;
}

int main()
{
  testNumIslands();
  return 0;
}
