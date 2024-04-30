#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 3 3 1 1
  // 2 2 1 2
  // 1 1 1 2
  // 首先观察得出，同一矩阵对角线的点 (i, j) 对应的 i - j 相等
  // 那么就把同一对角线的元素映射到新数组上，由于 i - j 可能小于0，
  // 可加上 offset >= max(j) 即可，为了方便我们取 m
  vector<vector<int>> diagonalSort(vector<vector<int>>& mat)
  {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int>> dummy(n + m);
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        // 从左到右，从上到下
        // 先把同一矩阵对角线的元素映射到新数组
        dummy[i - j + m].push_back(mat[i][j]);
      }
    }
    for (auto& arr : dummy)
    {
      // 排序按从大到小，为了后面逻辑方便
      std::sort(arr.begin(), arr.end(), std::greater<int>());
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        // 注意我们这里反着取元素
        mat[i][j] = dummy[i - j + m].back();
        dummy[i - j + m].pop_back();
      }
    }
    return mat;
  }
};
