#include <stdint.h>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<int> subSort(vector<int>& array)
  {
    int l = -1;
    int r = -1;
    int max = INT32_MIN;
    int min = INT32_MAX;
    int n = array.size();
    for (int i = 0; i < n; i++)
    {
      if (array[i] < max)
      {
        // 右侧值小于中间最大值，则会被中间序列包括
        r = i;
      }
      else
      {
        max = std::max(max, array[i]);
      }

      if (array[n - 1 - i] > min)
      {
        // 左侧值大于中间最小值，则会被中间序列包括
        l = n - 1 - i;
      }
      else
      {
        min = std::min(min, array[n - 1 - i]);
      }
    }
    return {l, r};
  }
};
