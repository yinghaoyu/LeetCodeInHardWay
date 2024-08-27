#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // dfs
  int numWays1(int n, vector<vector<int>>& relation, int k)
  {
    vector<vector<int>> edges(n);
    for (auto& e : relation)
    {
      int from = e[0];
      int to = e[1];
      edges[from].push_back(to);
    }
    return f(0, 0, n, k, edges);
  }

  int f(int i, int step, int n, int k, vector<vector<int>>& edges)
  {
    if (step == k)
    {
      return i == n - 1 ? 1 : 0;
    }
    int ans = 0;
    for (int to : edges[i])
    {
      ans += f(to, step + 1, n, k, edges);
    }
    return ans;
  }

  // bfs
  int numWays2(int n, vector<vector<int>>& relation, int k)
  {
    vector<vector<int>> edges(n);
    for (auto& e : relation)
    {
      int from = e[0];
      int to = e[1];
      edges[from].push_back(to);
    }

    int steps = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty() && steps < k)
    {
      steps++;
      int size = q.size();
      for (int i = 0; i < size; i++)
      {
        int index = q.front();
        q.pop();
        for (auto& next : edges[index])
        {
          q.push(next);
        }
      }
    }
    // 队列中剩下最后一轮所经过的节点
    int ways = 0;
    if (steps == k)
    {
      while (!q.empty())
      {
        if (q.front() == n - 1)
        {
          ways++;
        }
        q.pop();
      }
    }
    return ways;
  }

  int numWays3(int n, vector<vector<int>>& relation, int k)
  {
    // dp[i][j] 含义为经过 i 轮传递到编号 j 的玩家的方案数
    vector<vector<int>> dp(k + 1, vector<int>(n));
    // 第1轮一定位于编号0玩家
    dp[0][0] = 1;
    for (int i = 0; i < k; i++)
    {
      for (auto& edge : relation)
      {
        int src = edge[0], dst = edge[1];
        // 如果第 i 轮传递到编号 src 的玩家
        // 则第 i+1 轮可以从编号 src 的玩家传递到编号 dst 的玩家
        dp[i + 1][dst] += dp[i][src];
      }
    }
    return dp[k][n - 1];
  }
};
