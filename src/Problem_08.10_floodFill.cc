#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 private:
  static constexpr int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

 public:
  bool check(vector<vector<int>>& image, int x, int y, int oldColor)
  {
    return 0 <= x && x < image.size() && 0 <= y && y < image[0].size() && image[x][y] == oldColor;
  }

  void f(vector<vector<int>>& image, int x, int y, int newColor)
  {
    if (x < 0 || x >= image.size() || y < 0 || y > image[0].size() || image[x][y] == newColor)
    {
      return;
    }

    int oldColor = image[x][y];

    image[x][y] = newColor;

    for (int i = 0; i < 4; i++)
    {
      int nextx = x + directions[i][0];
      int nexty = y + directions[i][1];
      if (check(image, nextx, nexty, oldColor))
      {
        f(image, nextx, nexty, newColor);
      }
    }
  }

  // dfs
  vector<vector<int>> floodFill1(vector<vector<int>>& image, int sr, int sc, int newColor)
  {
    f(image, sr, sc, newColor);
    return image;
  }

  // bfs
  vector<vector<int>> floodFill2(vector<vector<int>>& image, int sr, int sc, int newColor)
  {
    int oldColor = image[sr][sc];
    if (oldColor == newColor)
    {
      return image;
    }
    int n = image.size();
    int m = image[0].size();
    queue<pair<int, int>> q;
    q.push({sr, sc});
    image[sr][sc] = newColor;
    while (!q.empty())
    {
      auto [x, y] = q.front();
      q.pop();
      for (int i = 0; i < 4; i++)
      {
        int nextx = x + directions[i][0];
        int nexty = y + directions[i][1];
        if (check(image, nextx, nexty, oldColor))
        {
          q.push({nextx, nexty});
          image[nextx][nexty] = newColor;
        }
      }
    }
    return image;
  }
};
