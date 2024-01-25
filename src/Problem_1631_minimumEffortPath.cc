#include <cmath>
#include <cstdint>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution
{
 private:
  class cmp
  {
   public:
    bool operator()(const std::tuple<int, int, int>& lhs, const std::tuple<int, int, int>& rhs)
    {
      return get<2>(lhs) > get<2>(rhs);
    }
  };

 public:
  int minimumEffortPath(vector<vector<int>>& heights)
  {
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int n = heights.size();
    int m = heights[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT32_MAX));
    distance[0][0] = 0;
    vector<vector<bool>> visited(n, vector<bool>(m));
    // 0 : 格子的行
    // 1 : 格子的列
    // 2 : 源点到当前格子的代价
    priority_queue<std::tuple<int, int, int>, vector<std::tuple<int, int, int>>, cmp> heap;
    heap.push({0, 0, 0});
    while (!heap.empty())
    {
      auto [x, y, c] = heap.top();
      heap.pop();
      if (x == n - 1 && y == m - 1)
      {
        return c;
      }
      visited[x][y] = true;
      for (int i = 0; i < 4; i++)
      {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny])
        {
          int nc = std::max(c, std::abs(heights[x][y] - heights[nx][ny]));
          if (nc < distance[nx][ny])
          {
            distance[nx][ny] = nc;
            heap.push({nx, ny, nc});
          }
        }
      }
    }
    return -1;
  }
};
