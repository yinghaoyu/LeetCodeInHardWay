#include <queue>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/01-matrix/
// @sa Problem_542_updateMatrix.cc
class Solution
{
 public:
  // bfs
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
};
