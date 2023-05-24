#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // bfs
  double frogPosition(int n, vector<vector<int>> &edges, int t, int target)
  {
    unordered_map<int, vector<int>> g;
    for (int i = 0; i < edges.size(); i++)
    {
      g[edges[i][0]].push_back(edges[i][1]);
      g[edges[i][1]].push_back(edges[i][0]);
    }
    double ans = 0.0;
    queue<tuple<int, int, double>> q;
    vector<bool> seen(n + 1);
    q.push({1, t, 1.0});
    while (!q.empty())
    {
      auto [cur, ttl, p] = q.front();
      q.pop();
      seen[cur] = true;
      int out = 0;
      for (auto &next : g[cur])
      {
        if (!seen[next])
        {
          out++;
        }
      }
      if (cur == target && (out == 0 || ttl == 0))
      {
        // 当节点没有出口，或者 ttl 结束
        ans = p;
        break;
      }
      for (auto &next : g[cur])
      {
        if (!seen[next] && ttl > 0)
        {
          q.push({next, ttl - 1, p / out});  // 这种做法会丢失精度
        }
      }
    }
    return ans;
  }
};

void testFrogPosition()
{
  Solution s;
  vector<vector<int>> e = {{1, 2}, {1, 3}, {1, 7}, {2, 4}, {2, 6}, {3, 5}};
  vector<vector<int>> e2 = {{2, 1}, {3, 2}};
  vector<vector<int>> e3 = {{2, 1}, {3, 2}, {4, 1}, {5, 1}, {6, 4}, {7, 1}, {8, 7}};
  vector<vector<int>> e4 = {{1, 2}};
  EXPECT_EQ_DOUBLE(0.16666, s.frogPosition(7, e, 2, 4));
  EXPECT_EQ_DOUBLE(0.33333, s.frogPosition(7, e, 1, 7));
  EXPECT_EQ_DOUBLE(1.0, s.frogPosition(3, e2, 1, 2));
  EXPECT_EQ_DOUBLE(0.0, s.frogPosition(8, e3, 7, 7));
  EXPECT_EQ_DOUBLE(1.0, s.frogPosition(2, e4, 10, 2));
  EXPECT_SUMMARY;
}

int main()
{
  testFrogPosition();
  return 0;
}
