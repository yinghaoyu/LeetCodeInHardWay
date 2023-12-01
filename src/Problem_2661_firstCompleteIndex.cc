#include <unordered_map>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat)
  {
    int n = mat.size();
    int m = mat[0].size();
    unordered_map<int, std::pair<int, int>> map;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        // 记录每个值对应的坐标
        map[mat[i][j]] = {i, j};
      }
    }
    vector<int> row(n);
    vector<int> col(m);
    for (int i = 0; i < arr.size(); i++)
    {
      auto& v = map[arr[i]];
      // 每遍历到行列就自增
      if (++row[v.first] == m)
      {
        // 说明这一列都填满了
        return i;
      }
      if (++col[v.second] == n)
      {
        // 说明这一行都填满了
        return i;
      }
    }
    return -1;
  }
};

void test()
{
  Solution s;
  vector<int> a1 = {1, 3, 4, 2};
  vector<vector<int>> m1 = {{1, 4}, {2, 3}};
  vector<int> a2 = {2, 8, 7, 4, 1, 3, 5, 6, 9};
  vector<vector<int>> m2 = {{3, 2, 5}, {1, 4, 6}, {8, 7, 9}};
  EXPECT_EQ_INT(2, s.firstCompleteIndex(a1, m1));
  EXPECT_EQ_INT(3, s.firstCompleteIndex(a2, m2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
