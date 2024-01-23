#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  int maxDistance(vector<vector<int>>& grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
    int seas = 0;
    vector<vector<bool>> visited(n, vector<bool>(m));
    queue<std::pair<int, int>> que;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == 1)
        {
          visited[i][j] = true;
          que.push({i, j});
        }
        else
        {
          visited[i][j] = false;
          seas++;
        }
      }
    }
    if (seas == 0 || seas == n * m)
    {
      return -1;
    }
    int level = 0;
    while (!que.empty())
    {
      level++;
      int size = que.size();
      for (int k = 0; k < size; k++)
      {
        auto [x, y] = que.front();
        que.pop();
        for (int i = 0; i < 4; i++)
        {
          int nx = x + directions[i][0];
          int ny = y + directions[i][1];
          if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny])
          {
            visited[nx][ny] = true;
            que.push({nx, ny});
          }
        }
      }
    }
    return level - 1;
  }
};
