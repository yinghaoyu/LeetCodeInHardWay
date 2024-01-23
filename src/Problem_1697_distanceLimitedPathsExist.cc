#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

#include "UnitTest.h"

using namespace std;

class UnionFind
{
 public:
  vector<int> parent;
  vector<int> size;
  vector<int> help;
  int number;

  UnionFind(int n)
  {
    parent = vector<int>(n);
    // 初始时，所有节点的父节点都是自己
    std::iota(parent.begin(), parent.end(), 0);
    // 初始时，每个集合的节点都只有一个
    size = vector<int>(n, 1);
    help = vector<int>(n);
    number = n;
  }

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
    int f1 = find(i);
    int f2 = find(j);
    if (f1 != f2)
    {
      if (size[f1] > size[f2])
      {
        size[f1] += size[f2];
        parent[f2] = f1;
      }
      else
      {
        size[f2] += size[f1];
        parent[f1] = f2;
      }
      number--;
    }
  }

  int getNumber() { return number; }
};

// 什么是 离线 ？
// 对于一道题目会给出若干询问，而这些询问是全部提前给出的，也就是说，你不必按照询问的顺序依次对它们进行处理，而是可以按照某种顺序（例如全序、偏序（拓扑序）、树的
// DFS 序等）或者把所有询问看成一个整体（例如整体二分、莫队算法等）进行处理。 与 离线 相对应的是
// 在线 思维，即所有的询问是依次给出的，在返回第 k 个询问的答案之前，不会获得第 k+1 个询问。

class Solution
{
 public:
  // 离线查询 + 并查集
  vector<bool> distanceLimitedPathsExist(int n,
                                         vector<vector<int>>& edgeList,
                                         vector<vector<int>>& queries)
  {
    // 将边按权值从小到大排序
    std::sort(edgeList.begin(), edgeList.end(),
              [](vector<int>& l, vector<int> r) { return l[2] < r[2]; });
    vector<int> idxs(queries.size());
    // 从0开始分配递增索引
    std::iota(idxs.begin(), idxs.end(), 0);
    // 将查询按照边权限制从小到大排序
    std::sort(idxs.begin(), idxs.end(),
              [&](int i, int j) { return queries[i][2] < queries[j][2]; });
    UnionFind uf(n);
    int i = 0;
    vector<bool> ans(queries.size());
    for (int query : idxs)
    {
      // 往并查集中添加边直到边权关系 dis_i < limit_j 不满足
      while (i < edgeList.size() && edgeList[i][2] < queries[query][2])
      {
        uf.unions(edgeList[i][0], edgeList[i][1]);
        i++;
      }
      // 使用并查集判断连通性
      ans[query] = uf.find(queries[query][0]) == uf.find(queries[query][1]);
    }
    return ans;
  }
};

bool isVectorEuqal(vector<bool> l, vector<bool> r)
{
  return l == r;
}

void testDistanceLimitedPathsExist()
{
  Solution s;
  vector<bool> n1 = {false, true};
  vector<vector<int>> e1 = {{0, 1, 2}, {1, 2, 4}, {2, 0, 8}, {1, 0, 16}};
  vector<vector<int>> q1 = {{0, 1, 2}, {0, 2, 5}};

  vector<bool> n2 = {true, false};
  vector<vector<int>> e2 = {{0, 1, 10}, {1, 2, 5}, {2, 3, 9}, {3, 4, 13}};
  vector<vector<int>> q2 = {{0, 4, 14}, {1, 4, 13}};
  EXPECT_TRUE(isVectorEuqal(n1, s.distanceLimitedPathsExist(3, e1, q1)));
  EXPECT_TRUE(isVectorEuqal(n2, s.distanceLimitedPathsExist(5, e2, q2)));
  EXPECT_SUMMARY;
}

int main()
{
  testDistanceLimitedPathsExist();
  return 0;
}
