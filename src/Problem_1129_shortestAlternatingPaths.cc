#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;
class Solution
{
 public:
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
  {
    vector<vector<vector<int>>> next(2, vector<vector<int>>(n));
    for (auto &e : redEdges)
    {
      // e[0] --> e[1] 的边为红色
      next[0][e[0]].push_back(e[1]);
    }
    for (auto &e : blueEdges)
    {
      // e[0] --> e[1] 的边为蓝色
      next[1][e[0]].push_back(e[1]);
    }
    // 两种类型的颜色最短路径的长度
    vector<vector<int>> dist(2, vector<int>(n, INT32_MAX));
    queue<pair<int, int>> q;
    // base case
    // 红边到0点的距离为0
    dist[0][0] = 0;
    // 蓝边到0点的距离为0
    dist[1][0] = 0;
    // 存在红边到0点
    q.push({0, 0});
    // 存在蓝边到0点
    q.push({0, 1});
    while (!q.empty())
    {
      auto [x, t] = q.front();
      q.pop();
      // 本次根据t类型的边到达x点
      // 翻转t类型的边，查询点x以1-t类型的出边
      for (auto y : next[1 - t][x])
      {
        if (dist[1 - t][y] != INT32_MAX)
        {
          // 过滤已经计算过的
          continue;
        }
        dist[1 - t][y] = dist[t][x] + 1;
        q.push({y, 1 - t});
      }
    }
    vector<int> answer(n);
    for (int i = 0; i < n; i++)
    {
      // 取红，蓝路径的最小值
      answer[i] = min(dist[0][i], dist[1][i]);
      if (answer[i] == INT32_MAX)
      {
        answer[i] = -1;
      }
    }
    return answer;
  }
};

bool isVectorEuqal(vector<int> a, vector<int> b)
{
  return a == b;
}

void testShortestAlternatingPaths()
{
  Solution s;
  vector<vector<int>> n1 = {{0, 1}, {1, 2}};
  vector<vector<int>> n2 = {};
  vector<int> o1 = {0, 1, -1};

  vector<vector<int>> n3 = {{0, 1}};
  vector<vector<int>> n4 = {{2, 1}};
  vector<int> o2 = {0, 1, -1};

  vector<vector<int>> n5 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
  vector<vector<int>> n6 = {{1, 2}, {2, 3}, {3, 1}};
  vector<int> o3 = {0, 1, 2, 3, 7};
  EXPECT_TRUE(isVectorEuqal(o1, s.shortestAlternatingPaths(3, n1, n2)));
  EXPECT_TRUE(isVectorEuqal(o2, s.shortestAlternatingPaths(3, n3, n4)));
  EXPECT_TRUE(isVectorEuqal(o3, s.shortestAlternatingPaths(5, n5, n6)));
  EXPECT_SUMMARY;
}

int main()
{
  testShortestAlternatingPaths();
  return 0;
}
