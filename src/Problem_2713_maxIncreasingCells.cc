#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 public:
  int maxIncreasingCells(vector<vector<int>>& mat)
  {
    int n = mat.size();
    int m = mat.size();
    map<int, vector<pair<int, int>>> map;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        // 先按值从小到大排序，这样才会让最终的步数最长
        map[mat[i][j]].push_back({i, j});
      }
    }

    // 记录每一行的最大单元格数
    vector<int> row(n);
    // 记录每一列的最大单元格数
    vector<int> col(m);

    vector<int> res;

    // 从最小值开始遍历
    for (auto& [_, p] : map)
    {
      res.clear();
      for (auto& [x, y] : p)
      {
        // 当前的结果从同行或同列的最大值跳过来
        // 当前值一定比前面的大，因为是排过序的
        res.push_back(std::max(row[x], row[y]) + 1);
      }
      for (int i = 0; i < n; i++)
      {
        auto& [x, y] = p[i];
        // 更新最大
        row[x] = std::max(row[x], res[i]);
        row[y] = std::max(row[y], res[i]);
      }
    }
    return *max_element(row.begin(), row.end());
  }
};
