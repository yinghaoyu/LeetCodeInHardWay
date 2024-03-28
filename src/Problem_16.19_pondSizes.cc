#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 private:
  class UnionFind
  {
   private:
    vector<int> father;
    vector<int> help;
    vector<int> size;
    int number;
    int col;

   public:
    UnionFind(vector<vector<int>>& land)
    {
      col = land[0].size();
      number = 0;
      int row = land.size();
      int len = row * col;
      vector<int> tmp(len, -1);
      father = tmp;
      help = tmp;
      size = tmp;
      for (int i = 0; i < row; i++)
      {
        for (int j = 0; j < col; j++)
        {
          if (land[i][j] == 0)
          {
            int idx = index(i, j);
            father[idx] = idx;
            size[idx] = 1;
            number++;
          }
        }
      }
    }

    // 把二维索引转化成一维
    int index(int i, int j) { return i * col + j; }

    void unions(int x1, int y1, int x2, int y2)
    {
      int i = index(x1, y1);
      int j = index(x2, y2);
      int fi = find(i);
      int fj = find(j);
      if (fi != fj)
      {
        if (size[fi] >= size[fj])
        {
          size[fi] += size[fj];
          size[fj] = -1;
          father[fj] = fi;
        }
        else
        {
          size[fj] += size[fi];
          size[fi] = -1;
          father[fi] = fj;
        }
        number--;
      }
    }

    int find(int i)
    {
      int hi = 0;
      while (father[i] != i)
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

    int sets() { return number; }

    vector<int> dump()
    {
      size.erase(std::remove(size.begin(), size.end(), -1), size.end());
      std::sort(size.begin(), size.end());
      return size;
    }
  };

 public:
  // 并查集
  vector<int> pondSizes(vector<vector<int>>& land)
  {
    int n = land.size();
    int m = land[0].size();
    UnionFind uf(land);
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (i + 1 < n && land[i][j] == 0 && land[i + 1][j] == 0)
        {
          uf.unions(i, j, i + 1, j);
        }
        if (j + 1 < m && land[i][j] == 0 && land[i][j + 1] == 0)
        {
          uf.unions(i, j, i, j + 1);
        }
        if (i + 1 < n && j + 1 < m && land[i][j] == 0 && land[i + 1][j + 1] == 0)
        {
          uf.unions(i, j, i + 1, j + 1);
        }
        if (i - 1 >= 0 && j + 1 < m && land[i][j] == 0 && land[i - 1][j + 1] == 0)
        {
          uf.unions(i, j, i - 1, j + 1);
        }
        if (i + 1 < n && j - 1 >= 0 && land[i][j] == 0 && land[i + 1][j - 1] == 0)
        {
          uf.unions(i, j, i + 1, j - 1);
        }
      }
    }
    return uf.dump();
  }

  // dfs
  vector<int> f(vector<vector<int>>& land)
  {
    int m = land.size();
    int n = land[0].size();
    std::function<int(int, int)> dfs = [&](int x, int y) -> int
    {
      if (x < 0 || x >= m || y < 0 || y >= n || land[x][y] != 0)
      {
        return 0;
      }
      int ans = 1;
      land[x][y] = -1;
      for (int dx = -1; dx <= 1; dx++)
      {
        for (int dy = -1; dy <= 1; dy++)
        {
          if (dx == 0 && dy == 0)
          {
            continue;
          }
          ans += dfs(x + dx, y + dy);
        }
      }
      return ans;
    };
    vector<int> ans;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (land[i][j] == 0)
        {
          ans.push_back(dfs(i, j));
        }
      }
    }
    std::sort(ans.begin(), ans.end());
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{0, 2, 1, 0}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 1, 0, 1}};
  vector<int> o1 = {1, 2, 4};
  EXPECT_TRUE(o1 == s.pondSizes(n1));
  EXPECT_TRUE(o1 == s.f(n1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
