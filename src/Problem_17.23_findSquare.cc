#include <vector>

using namespace std;

// 扩展题 最大正方形 Problem_0221_maximalSquare.cc
// @sa https://leetcode.cn/problems/maximal-square/
class Solution
{
 public:
  vector<int> findSquare(vector<vector<int>>& matrix)
  {
    int n = matrix.size();
    // left[i][j]表示坐标(i-1, j-1)及左边最大连续0的数量
    vector<vector<int>> left(n + 1, vector<int>(n + 1));
    // up[i][j]表示坐标(i-1, j-1)及上边最大连续0的数量
    vector<vector<int>> up(n + 1, vector<int>(n + 1));
    int r = 0;
    int c = 0;
    int size = 0;
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if (matrix[i - 1][j - 1] == 0)
        {
          //                      检测上侧边 (i-border+1, j)
          //                   --------------
          //          检      |              |
          //          测      |              |
          //          左      |              | border
          //          侧      |              |
          //          边      |              |
          //                  |              |
          // (i, j-border+1)  --------------
          //                      border   (i,j)
          left[i][j] = left[i][j - 1] + 1;
          up[i][j] = up[i - 1][j] + 1;
          int border = std::min(left[i][j], up[i][j]);
          while (left[i - border + 1][j] < border || up[i][j - border + 1] < border)
          {
            border--;
          }
          // 由于计算的顺序是 i 和 j递增的，所以如果有多个方阵大小一样
          // 那么返回的下标一定满足左上角行下标最小，
          // 当存在左上角行下标并列最小的情况时时满足左上角列下标最小
          if (border > size)
          {
            // 由于坐标是从(0,0)开始，所以需要 -1
            r = i - border;
            c = j - border;
            size = border;
          }
        }
      }
    }
    if (size > 0)
    {
      return {r, c, size};
    }
    else
    {
      return {};
    }
  }
};
