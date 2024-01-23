#include <stdint.h>
#include <deque>
#include <vector>

using namespace std;

class Solution
{
 public:
  int minimumObstacles(vector<vector<int>>& grid)
  {
    constexpr int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int>(n, 1e9));
    deque<std::pair<int, int>> q;
    q.push_front({0, 0});
    distance[0][0] = 0;
    while (!q.empty())
    {
      auto [x, y] = q.front();
      q.pop_front();
      if (x == m - 1 && y == n - 1)
      {
        return distance[x][y];
      }
      for (int i = 0; i < 4; i++)
      {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
            distance[x][y] + grid[nx][ny] < distance[nx][ny])
        {
          distance[nx][ny] = distance[x][y] + grid[nx][ny];
          if (grid[nx][ny] == 0)
          {
            // 优先走最短路径，可以对常数时间进行优化
            // 当然也可以删除这部分逻辑，所有bfs走完，返回distance[m - 1][n - 1]即可
            q.push_front({nx, ny});
          }
          else
          {
            q.push_back({nx, ny});
          }
        }
      }
    }
    return -1;
  }
};
