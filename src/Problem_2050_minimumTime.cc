#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

// @sa https://www.bilibili.com/video/BV12y4y1F79q/
class Solution
{
 public:
  // 记忆化搜索
  int minimumTime1(int n, vector<vector<int>>& relations, vector<int>& time)
  {
    int max = 0;
    unordered_map<int, vector<int>> g;
    for (auto& e : relations)
    {
      int from = e[0];
      int to = e[1];
      g[from].push_back(to);
    }
    unordered_map<int, int> map;
    function<int(int)> dp = [&](int i)
    {
      if (!map.count(i))
      {
        int cur = 0;
        for (int next : g[i])
        {
          cur = std::max(cur, dp(next));
        }
        cur += time[i - 1];
        map[i] = cur;
      }
      return map[i];
    };
    for (int i = 1; i <= n; i++)
    {
      max = std::max(max, dp(i));
    }
    return max;
  }

  // 拓扑排序
  int minimumTime2(int n, vector<vector<int>>& relations, vector<int>& time)
  {
    vector<vector<int>> g(n);
    // 每个节点的入度
    vector<int> in(n);
    for (auto& e : relations)
    {
      int a = e[0] - 1, b = e[1] - 1;
      g[a].push_back(b);
      ++in[b];
    }
    queue<int> q;
    // cost[i]表示课程最早的完成时间
    vector<int> cost(n);
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
      int v = in[i], t = time[i];
      if (v == 0)
      {
        // 入度为 0 的点，先入队
        q.push(i);
        cost[i] = t;
        ans = max(ans, t);
      }
    }
    while (!q.empty())
    {
      int i = q.front();
      q.pop();
      for (int j : g[i])
      {
        if (--in[j] == 0)
        {
          q.push(j);
        }
        // 每门课程的最早完成时间 = max(依赖课程的最早完成时间 + 当前课程花费的时间)
        cost[j] = max(cost[j], cost[i] + time[j]);
        ans = max(ans, cost[j]);
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 3}, {2, 3}};
  vector<int> t1 = {3, 2, 5};
  vector<vector<int>> n2 = {{1, 5}, {2, 5}, {3, 5}, {3, 4}, {4, 5}};
  vector<int> t2 = {1, 2, 3, 4, 5};
  EXPECT_EQ_INT(8, s.minimumTime1(3, n1, t1));
  EXPECT_EQ_INT(12, s.minimumTime1(5, n2, t2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
