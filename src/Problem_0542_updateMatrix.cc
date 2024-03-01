#include <stdint.h>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // bfs
  // 从 0 节点开始进行广度遍历
  vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
  {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int>> distance(n, vector<int>(m));
    vector<vector<bool>> seen(n, vector<bool>(m));
    queue<std::pair<int, int>> q;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (mat[i][j] == 0)
        {
          q.push({i, j});
          seen[i][j] = true;
        }
      }
    }
    static constexpr int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (!q.empty())
    {
      auto [x, y] = q.front();
      q.pop();
      for (int i = 0; i < 4; i++)
      {
        int nextx = x + directions[i][0];
        int nexty = y + directions[i][1];
        if (nextx >= 0 && nextx < n && nexty >= 0 && nexty < m && !seen[nextx][nexty])
        {
          distance[nextx][nexty] = distance[x][y] + 1;
          q.push({nextx, nexty});
          seen[nextx][nexty] = true;
        }
      }
    }
    return distance;
  }

  // 动态规划
  vector<vector<int>> dp(vector<vector<int>>& matrix)
  {
    int m = matrix.size();
    int n = matrix[0].size();
    // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
    vector<vector<int>> dist(m, vector<int>(n, INT32_MAX / 2));
    // 如果 (i, j) 的元素为 0，那么距离为 0
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (matrix[i][j] == 0)
        {
          dist[i][j] = 0;
        }
      }
    }
    // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i - 1 >= 0)
        {
          dist[i][j] = std::min(dist[i][j], dist[i - 1][j] + 1);
        }
        if (j - 1 >= 0)
        {
          dist[i][j] = std::min(dist[i][j], dist[i][j - 1] + 1);
        }
      }
    }
    // 只有 水平向左移动 和 竖直向下移动，注意动态规划的计算顺序
    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = 0; j < n; j++)
      {
        if (i + 1 < m)
        {
          dist[i][j] = std::min(dist[i][j], dist[i + 1][j] + 1);
        }
        if (j - 1 >= 0)
        {
          dist[i][j] = std::min(dist[i][j], dist[i][j - 1] + 1);
        }
      }
    }
    // 只有 水平向右移动 和 竖直向上移动，注意动态规划的计算顺序
    for (int i = 0; i < m; i++)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        if (i - 1 >= 0)
        {
          dist[i][j] = std::min(dist[i][j], dist[i - 1][j] + 1);
        }
        if (j + 1 < n)
        {
          dist[i][j] = std::min(dist[i][j], dist[i][j + 1] + 1);
        }
      }
    }
    // 只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        if (i + 1 < m)
        {
          dist[i][j] = std::min(dist[i][j], dist[i + 1][j] + 1);
        }
        if (j + 1 < n)
        {
          dist[i][j] = std::min(dist[i][j], dist[i][j + 1] + 1);
        }
      }
    }
    return dist;
  }
};
