#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> findSwapValues(vector<int>& array1, vector<int>& array2)
  {
    int sum1 = 0;
    int sum2 = 0;
    for (int num : array1)
    {
      sum1 += num;
    }
    for (int num : array2)
    {
      sum2 += num;
    }
    // 若存在 x 和 y，则交换后满足
    // sum1 - x + y = sum2 - y + x
    // sum1 - sum2 = 2 * (x - y)
    // sum1 - sum2 必须为偶数
    int diff = sum1 - sum2;
    if (diff & 1)
    {
      return {};
    }
    // x - y = diff / 2
    diff /= 2;
    unordered_set<int> s(array1.begin(), array1.end());
    for (auto& num : array2)
    {
      // y + diff / 2 = x
      if (s.count(num + diff))
      {
        return {num + diff, num};
      }
    }
    return {};
  }
};
