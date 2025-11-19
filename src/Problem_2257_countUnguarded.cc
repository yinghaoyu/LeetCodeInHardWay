#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls)
  {
    vector grid(m, vector<int>(n));

    // x坐标, y坐标, 方向
    queue<tuple<int, int, int>> q;

    vector<vector<int>> direction = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    // 初始化警卫
    for (const auto& guard : guards)
    {
      grid[guard[0]][guard[1]] = -1;
      for (int i = 0; i < 4; i++)
      {
        // 四个方向进行搜索
        q.emplace(guard[0], guard[1], i);
      }
    }

    // 初始化墙
    for (const auto& wall : walls)
    {
      grid[wall[0]][wall[1]] = -2;
    }

    // bfs
    while (!q.empty())
    {
      auto [x, y, i] = q.front();
      q.pop();
      int nextx = x + direction[i][0];
      int nexty = y + direction[i][1];
      // 沿着视线方向的下一个坐标合法，且不为警卫或墙
      if (nextx >= 0 && nextx < m && nexty >= 0 && nexty < n && grid[nextx][nexty] >= 0)
      {
        // 对应状态未遍历过
        if ((grid[nextx][nexty] & (1 << i)) == 0)
        {
          grid[nextx][nexty] |= (1 << i);
          q.emplace(nextx, nexty, i);
        }
      }
    }

    // 统计
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (grid[i][j] == 0)
        {
          ans++;
        }
      }
    }
    return ans;
  }
};
