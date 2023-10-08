#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 private:
  int binarySearch(vector<int> &arr, int target)
  {
    int left = 0;
    int right = arr.size() - 1;
    // 为什么这里取 n ?
    // 因为如果找不到 target <= arr[i]，说明所有的数都 < target
    int index = arr.size();
    while (left <= right)
    {
      int mid = (right - left) / 2 + left;
      if (target <= arr[mid])
      {
        // 找到左边第一个 >= target 的数
        index = mid;
        right = mid - 1;
      }
      else
      {
        left = mid + 1;
      }
    }
    return index;
  }

 public:
  // 二分查找
  vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &people)
  {
    int n = flowers.size();
    vector<int> start(n);
    vector<int> end(n);
    for (int i = 0; i < n; i++)
    {
      start[i] = flowers[i][0];
      end[i] = flowers[i][1];
    }
    std::sort(start.begin(), start.end());
    std::sort(end.begin(), end.end());
    vector<int> ans;
    for (int p : people)
    {
      // 找到所有开花时间 <= 当前人到达时间的花，开花数
      int x = binarySearch(start, p + 1);
      // 找到所有凋零时间 < 当前人到达时间的花，凋零数
      int y = binarySearch(end, p);
      // 相减得到花期内的数
      ans.push_back(x - y);
    }
    return ans;
  }
  // TODO: 差分
};
