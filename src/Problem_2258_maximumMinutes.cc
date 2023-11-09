#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
 private:
  const int INF = 1e9;
  const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

 public:
  int maximumMinutes(vector<vector<int>>& grid)
  {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> fireTime(m, vector<int>(n, INF));
    bfs(grid, fireTime);
    int ans = -1;
    int low = 0;
    int high = m * n;
    while (low <= high)
    {
      int mid = low + (high - low) / 2;
      if (check(fireTime, grid, mid))
      {
        ans = mid;
        low = mid + 1;
      }
      else
      {
        high = mid - 1;
      }
    }
    return ans >= m * n ? 1e9 : ans;
  }

  // 广度遍历计算每个节点着火的时间
  void bfs(vector<vector<int>>& grid, vector<vector<int>>& fireTime)
  {
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (grid[i][j] == 1)
        {
          q.emplace(i, j);
          fireTime[i][j] = 0;
        }
      }
    }
    int time = 1;
    while (!q.empty())
    {
      int size = q.size();
      for (int i = 0; i < size; i++)
      {
        auto [cx, cy] = q.front();
        q.pop();
        for (int j = 0; j < 4; j++)
        {
          int nx = cx + dirs[j][0];
          int ny = cy + dirs[j][1];
          if (nx >= 0 && ny >= 0 && nx < m && ny < n)
          {
            if (grid[nx][ny] == 2 || fireTime[nx][ny] != INF)
            {
              // 遇到墙，或者已经着火
              continue;
            }
            q.emplace(nx, ny);
            fireTime[nx][ny] = time;
          }
        }
      }
      time++;
    }
  }

  bool check(vector<vector<int>>& fireTime, vector<vector<int>>& grid, int stayTime)
  {
    int m = fireTime.size();
    int n = fireTime[0].size();
    vector<vector<bool>> visit(m, vector<bool>(n, false));
    queue<tuple<int, int, int>> q;
    // 等待的时间
    q.emplace(0, 0, stayTime);
    visit[0][0] = true;
    while (!q.empty())
    {
      auto [cx, cy, time] = q.front();
      q.pop();
      for (int i = 0; i < 4; i++)
      {
        int nx = cx + dirs[i][0];
        int ny = cy + dirs[i][1];
        if (nx >= 0 && ny >= 0 && nx < m && ny < n)
        {
          if (visit[nx][ny] || grid[nx][ny] == 2)
          {
            // 已经走过，或者是墙
            continue;
          }
          if (nx == m - 1 && ny == n - 1)
          {
            // 到达终点
            return fireTime[nx][ny] >= time + 1;
          }
          if (fireTime[nx][ny] > time + 1)
          {
            // 着火的时间晚于到达的时间，说明可以到达这个节点
            q.emplace(nx, ny, time + 1);
            visit[nx][ny] = true;
          }
        }
      }
    }
    return false;
  }
};
