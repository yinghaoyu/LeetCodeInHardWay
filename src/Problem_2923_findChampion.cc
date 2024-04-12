#include <vector>

using namespace std;

class Solution
{
 public:
  int findChampion(vector<vector<int>>& grid)
  {
    int n = grid.size();
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
      if (grid[i][ans] == 1)
      {
        // 找到一个比 ans 大的，就更新 ans，记之前的 ans 为 pre
        // 因为之前遍历的元素都不大于pre，也不会大于当前的ans，因此直接从 i + 1 开始继续往后找
        ans = i;
      }
    }
    return ans;
  }
};
