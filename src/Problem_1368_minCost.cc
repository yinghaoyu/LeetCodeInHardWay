#include <deque>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 public:
  int minCost(vector<vector<int>>& grid)
  {
    // 格子的数值 :
    // 1 右
    // 2 左
    // 3 下
    // 4 上
    vector<vector<int>> directions = {{}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int>(n, 1e6 + 1));
    deque<std::pair<int, int>> que;
    que.push_front({0, 0});
    distance[0][0] = 0;
    while (!que.empty())
    {
      auto [x, y] = que.front();
      que.pop_front();
      if (x == m - 1 && y == n - 1)
      {
        return distance[x][y];
      }
      for (int i = 1; i <= 4; i++)
      {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        // 所有不同方向的认为距离 1(需要修改)， 同方向的认为距离0(不需要修改)
        int weight = grid[x][y] != i ? 1 : 0;
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && distance[x][y] + weight < distance[nx][ny])
        {
          distance[nx][ny] = distance[x][y] + weight;
          if (weight == 0)
          {
            // 常数时间优化，也可以删除这部分逻辑，
            // 但是需要把所有bfs走完，返回distance[m-1][n-1]
            que.push_front({nx, ny});
          }
          else
          {
            que.push_back({nx, ny});
          }
        }
      }
    }
    return -1;
  }
};
