#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 贪心
  int twoCitySchedCost(vector<vector<int>>& costs)
  {
    int n = costs.size();
    vector<int> arr(n);
    int sum = 0;
    // 假设先让所有人都往 a 走，需要费用 sum
    for (int i = 0; i < n; i++)
    {
      arr[i] = costs[i][1] - costs[i][0];
      sum += costs[i][0];
    }
    // 再从费用差价最小的前 n 个人，替换到往 b 走
    std::sort(arr.begin(), arr.end());
    int m = n / 2;
    for (int i = 0; i < m; i++)
    {
      sum += arr[i];
    }
    return sum;
  }
};
