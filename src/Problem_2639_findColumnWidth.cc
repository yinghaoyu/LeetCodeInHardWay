#include <vector>

using namespace std;

class Solution
{
 private:
  int getLength(int num)
  {
    int len = num <= 0 ? 1 : 0;
    while (num != 0)
    {
      num /= 10;
      len++;
    }
    return len;
  }

 public:
  vector<int> findColumnWidth(vector<vector<int>>& grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<int> ans(m);
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        ans[j] = std::max(ans[j], getLength(grid[i][j]));
      }
    }
    return ans;
  }
};
