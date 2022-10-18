#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

using TdArray = vector<vector<int>>;

class colors
{
  // 误区：以为从有向图中找环
  // 实际上 1 -> 2 -> 3 -> 4 -> 1 也能分成 {1， 3} {2， 4}两组
  // 用染色法区分是否二分图，即相邻的节点染的颜色不同
  // 00 表示未染色，01 表示红，10 表示蓝
  // 11 ^ 01 = 10
  // 11 ^ 10 = 01 用11进行异或运算，刚好可以切换两种颜色
 public:
  bool dfs(int cur, int dye, vector<int> &color, const TdArray &g)
  {
    color[cur] = dye;
    for (auto &next : g[cur])
    {
      if (color[next] != 0 && color[next] == color[cur])
      {
        // 相邻的节点颜色一样，说明不是二分图
        return false;
      }
      if (color[next] == 0 && !dfs(next, 3 ^ dye, color, g))
      {
        // 相邻的节点没染色，染上不同的颜色
        return false;
      }
    }
    return true;
  }

  bool possibleBipartition1(int n, TdArray &dislikes)
  {
    vector<int> color(n + 1);  // 0 号位置不用
    TdArray g(n + 1);
    for (auto &p : dislikes)
    {
      g[p[0]].push_back(p[1]);
      g[p[1]].push_back(p[0]);
    }
    // 由于有color限制，每个节点只会遍历一次
    // 时间复杂度为O(n + m)，其中 n 题目给定的人数，m 为给定的 dislike 数组的大小
    for (int i = 1; i <= n; i++)
    {
      // 这里一定要遍历所有i，因为可能不止包含一个连通块
      if (color[i] == 0 && !dfs(i, 1, color, g))
      {
        return false;
      }
    }
    return true;
  }

  // bfs
  bool possibleBipartition2(int n, TdArray &dislikes)
  {
    vector<int> color(n + 1, 0);
    TdArray g(n + 1);
    for (auto &p : dislikes)
    {
      g[p[0]].push_back(p[1]);
      g[p[1]].push_back(p[0]);
    }
    for (int i = 1; i <= n; ++i)
    {
      if (color[i] == 0)
      {
        queue<int> q;
        q.push(i);
        color[i] = 1;
        while (!q.empty())
        {
          auto t = q.front();
          q.pop();
          for (auto &next : g[t])
          {
            if (color[next] != 0 && color[next] == color[t])
            {
              return false;
            }
            if (color[next] == 0)
            {
              color[next] = 3 ^ color[t];
              q.push(next);
            }
          }
        }
      }
    }
    return true;
  }

  class UnionFind
  {
   private:
    // parent[i] = k ： i的父亲是k
    vector<int> parent;
    // size[i] = k ： 如果i是代表节点，size[i]才有意义，否则无意义
    // i所在的集合大小是多少
    vector<int> size;
    // 辅助结构，用于记录路径上的节点，压缩路径
    vector<int> help;
    // 一共有多少个集合
    int number;

   public:
    UnionFind(int N)
    {
      vector<int> tmp(N);
      parent = tmp;
      size = tmp;
      help = tmp;
      number = N;
      for (int i = 0; i < N; i++)
      {
        parent[i] = i;  // 初始时i的父亲是自己
        size[i] = 1;    // 只有一个节点
      }
    }

    // 从i开始一直往上，往上到不能再往上，代表节点，返回
    // 这个过程要做路径压缩
    int find(int i)
    {
      int hi = 0;
      while (i != parent[i])
      {
        help[hi++] = i;  // 标记所有不同编号的节点
        i = parent[i];
      }
      for (hi--; hi >= 0; hi--)
      {
        parent[help[hi]] = i;  // 把所有节点的父亲标记为根节点
      }
      return i;  // 返回这个节点的根节点
    }

    void unions(int i, int j)
    {
      int f1 = find(i);  // 节点i的根节点
      int f2 = find(j);  // 节点j的根节点
      if (f1 != f2)
      {
        if (size[f1] >= size[f2])
        {
          // 多的吞并少的
          size[f1] += size[f2];
          parent[f2] = f1;
        }
        else
        {
          size[f2] += size[f1];
          parent[f1] = f2;
        }
        number--;  // 吞并完集合减少1个
      }
    }

    int sets() { return number; }
  };

  // 并查集
  bool possibleBipartition3(int n, TdArray &dislikes)
  {
    UnionFind u(n + 1);
    TdArray g(n + 1);
    for (auto &p : dislikes)
    {
      g[p[0]].push_back(p[1]);
      g[p[1]].push_back(p[0]);
    }
    for (int i = 1; i <= n; ++i)
    {
      for (int j = 0; j < g[i].size(); ++j)
      {
        // 把与 i 相邻的节点放入并查集中
        u.unions(g[i][0], g[i][j]);
        if (u.find(i) == u.find(g[i][j]))
        {
          // 如果 i 和任意相邻的节点在一个集合中，说明不是二分图
          return false;
        }
      }
    }
    return true;
  }
};

void testPossibleBipartition()
{
  colors s;
  TdArray d1 = {{1, 2}, {1, 3}, {2, 4}};

  TdArray d2 = {{1, 2}, {1, 3}, {2, 3}};

  TdArray d3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}};

  EXPECT_TRUE(s.possibleBipartition1(4, d1));
  EXPECT_FALSE(s.possibleBipartition1(3, d2));
  EXPECT_FALSE(s.possibleBipartition1(5, d2));

  EXPECT_TRUE(s.possibleBipartition2(4, d1));
  EXPECT_FALSE(s.possibleBipartition2(3, d2));
  EXPECT_FALSE(s.possibleBipartition2(5, d2));

  EXPECT_TRUE(s.possibleBipartition3(4, d1));
  EXPECT_FALSE(s.possibleBipartition3(3, d2));
  EXPECT_FALSE(s.possibleBipartition3(5, d2));
  EXPECT_SUMMARY;
}

int main()
{
  testPossibleBipartition();
  return 0;
}
