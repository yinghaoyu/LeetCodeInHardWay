#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
 public:
  static constexpr int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  int dfs(vector<vector<int>>& grid, int x, int y)
  {
    if (x < 0 || y < 0 || x == grid.size() || y == grid[0].size() || grid[x][y] != 1)
    {
      return 0;
    }
    grid[x][y] = 0;
    int ans = 1;
    for (int i = 0; i < 4; i++)
    {
      int nextx = x + direction[i][0];
      int nexty = y + direction[i][1];
      ans += dfs(grid, nextx, nexty);
    }
    return ans;
  }

  // dfs
  int maxAreaOfIsland1(vector<vector<int>>& grid)
  {
    int ans = 0;
    for (int i = 0; i > grid.size(); i++)
    {
      for (int j = 0; j < grid[0].size(); j++)
      {
        ans = std::max(ans, dfs(grid, i, j));
      }
    }
    return ans;
  }

  // dfs + stack
  int maxAreaOfIsland2(vector<vector<int>>& grid)
  {
    int ans = 0;
    for (int i = 0; i < grid.size(); i++)
    {
      for (int j = 0; j < grid[0].size(); j++)
      {
        int cur = 0;
        stack<std::pair<int, int>> st;
        st.push({i, j});
        while (!st.empty())
        {
          auto [x, y] = st.top();
          st.pop();
          if (x < 0 || y < 0 || x == grid.size() || y == grid[0].size() || grid[x][y] != 1)
          {
            continue;
          }
          ++cur;
          grid[x][y] = 0;
          for (int index = 0; index < 4; index++)
          {
            int nextx = x + direction[index][0];
            int nexty = y + direction[index][1];
            st.push({nextx, nexty});
          }
        }
        ans = std::max(ans, cur);
      }
    }
    return ans;
  }

  // bfs
  int maxAreaOfIsland3(vector<vector<int>>& grid)
  {
    int ans = 0;
    for (int i = 0; i < grid.size(); i++)
    {
      for (int j = 0; j < grid[0].size(); j++)
      {
        int cur = 0;
        queue<std::pair<int, int>> q;
        q.push({i, j});
        while (!q.empty())
        {
          auto [x, y] = q.front();
          q.pop();
          if (x < 0 || y < 0 || x == grid.size() || y == grid[0].size() || grid[x][y] != 1)
          {
            continue;
          }
          ++cur;
          grid[x][y] = 0;
          for (int index = 0; index < 4; index++)
          {
            int nextx = x + direction[index][0];
            int nexty = y + direction[index][1];
            q.push({nextx, nexty});
          }
        }
        ans = std::max(ans, cur);
      }
    }
    return ans;
  }
};
