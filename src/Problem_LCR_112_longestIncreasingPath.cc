#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/
// @sa Problem_0329_longestIncreasingPath.cc
class Solution
{
 public:
  int longestIncreasingPath(vector<vector<int>>& matrix)
  {
    int n = matrix.size();
    int m = matrix[0].size();
    int ans = 0;
    vector<vector<int>> visited(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        ans = std::max(ans, lip(matrix, i, j, visited));
      }
    }
    return ans;
  }

  int lip(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& visited)
  {
    if (visited[i][j] != 0)
    {
      return visited[i][j];
    }
    int next = 0;
    if (canWalk(matrix, i, j, i + 1, j))
    {
      next = std::max(next, lip(matrix, i + 1, j, visited));
    }
    if (canWalk(matrix, i, j, i - 1, j))
    {
      next = std::max(next, lip(matrix, i - 1, j, visited));
    }
    if (canWalk(matrix, i, j, i, j + 1))
    {
      next = std::max(next, lip(matrix, i, j + 1, visited));
    }
    if (canWalk(matrix, i, j, i, j - 1))
    {
      next = std::max(next, lip(matrix, i, j - 1, visited));
    }
    visited[i][j] = next + 1;
    return visited[i][j];
  }

  bool canWalk(vector<vector<int>>& matrix, int a, int b, int c, int d)
  {
    return c >= 0 && c < matrix.size() && d >= 0 && d < matrix[0].size() &&
           matrix[a][b] < matrix[c][d];
  }
};
