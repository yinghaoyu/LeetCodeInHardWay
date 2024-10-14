#include <stdint.h>
#include <algorithm>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/solutions/2798247/li-yong-and-de-xing-zhi-pythonjavacgo-by-mjx7/
class Solution
{
 public:
  int closestToTarget(vector<int>& arr, int target)
  {
    int ans = INT32_MAX;
    for (int i = 0; i < arr.size(); i++)
    {
      int x = arr[i];
      // 单个元素先计算结果
      ans = std::min(ans, abs(x - target));
      // 首先数之间的与操作一定会让结果不变或者变小
      // 利用集合理解，A ∩ B = A，那么 A 是 B 的子集
      for (int j = i - 1; j >= 0 && (arr[j] & x) != arr[j]; j--)
      {
        arr[j] &= x;
        ans = std::min(ans, abs(arr[j] - target));
      }
    }
    return ans;
  }
};
