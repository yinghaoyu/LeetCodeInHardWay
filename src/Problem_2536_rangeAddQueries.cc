#include <vector>

using namespace std;

// 二维差分 + 二维前缀和
class Solution
{
 public:
  vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries)
  {
    vector diff(n + 1, vector<int>(n + 1));
    for (const auto& q : queries)
    {
      int rowA = q[0];
      int colA = q[1];
      int rowB = q[2];
      int colB = q[3];
      diff[rowA][colA] += 1;
      diff[rowB + 1][colA] -= 1;
      diff[rowA][colB + 1] -= 1;
      diff[rowB + 1][colB + 1] += 1;
    }

    vector ans(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        int x1 = i == 0 ? 0 : ans[i - 1][j];
        int x2 = j == 0 ? 0 : ans[i][j - 1];
        int x3 = (i == 0 || j == 0) ? 0 : ans[i - 1][j - 1];
        ans[i][j] = diff[i][j] + x1 + x2 - x3;
      }
    }

    return ans;
  }
};
