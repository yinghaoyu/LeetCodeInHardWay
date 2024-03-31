#include <queue>
#include <tuple>
#include <vector>

using namespace std;

// TODO: figure it out.
// @sa https://www.bilibili.com/video/BV1Dw411w7P5/ Code06
class Solution
{
 private:
  class cmp
  {
   public:
    bool operator()(const tuple<int, int, int>& lhs, const tuple<int, int, int>& rhs)
    {
      return get<2>(lhs) > get<2>(rhs);
    }
  };

 public:
  // bfs + 优先级队列
  int trapRainWater(vector<vector<int>>& heightMap)
  {
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int n = heightMap.size();
    int m = heightMap[0].size();
    // 0 : 行
    // 1 : 列
    // 2 : 水线
    // 小根堆，按水线从底到高排序
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, cmp> heap;
    vector<vector<bool>> visited(n, vector<bool>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
        {
          // 把边界处的格子进堆
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
      // 水线高度 - 当前格子的高度，就是这个格子的储水量
      ans += w - heightMap[r][c];
      for (int i = 0; i < 4; i++)
      {
        int nr = r + directions[i][0];
        int nc = c + directions[i][1];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc])
        {
          // 8 8 4 8
          // 8 2 5 6
          // 8 8 8 8
          // 8 8 8 8
          // 例如在位置 heightMap[1][2] = 5，此时的水线为 4，
          // 但是对位置 heightMap[1][1] = 2 来讲，水线应该取 std::max(5, 4)
          heap.push({nr, nc, std::max(heightMap[nr][nc], w)});
          visited[nr][nc] = true;
        }
      }
    }
    return ans;
  }
};
