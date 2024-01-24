#include <queue>
#include <tuple>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 private:
  class cmp
  {
   public:
    bool operator()(const tuple<int, int, int>& lhs, const tuple<int, int, int>& rhs)
    {
      return get<2>(lhs) < get<2>(rhs);
    }
  };

 public:
  int trapRainWater(vector<vector<int>>& heightMap)
  {
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int n = heightMap.size();
    int m = heightMap[0].size();
    // 0 : 行
    // 1 : 列
    // 2 : 水线
    // 按水线从高到底排序
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, cmp> heap;
    vector<vector<bool>> visited(n, vector<bool>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
        {
          // 边界
          heap.push({i, j, heightMap[i][j]});
          visited[i][j] = true;
        }
        else
        {
          visited[i][j] = false;
        }
      }
    }
    int ans = 0;
    while (!heap.empty())
    {
      auto [r, c, w] = heap.top();
      heap.pop();
      ans += w - heightMap[r][c];
      for (int i = 0; i < 4; i++)
      {
        int nr = r + directions[i][0];
        int nc = c + directions[i][1];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc])
        {
          heap.push({nr, nc, std::max(heightMap[nr][nc], w)});
          visited[nr][nc] = true;
        }
      }
    }
    return ans;
  }
};
