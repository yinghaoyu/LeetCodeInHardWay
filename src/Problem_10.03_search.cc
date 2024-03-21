#include <vector>

using namespace std;

// 旋转数组
// 此题是第 81 题的进阶，存在相同的值，且查找最左边的
class Solution
{
 public:
  // 思路 - 二分查找
  // 1、先判断数组左半数组还是右半数组升序
  // 2、然后再进行二分查找
  // 3、最后对重复值或结果进行判断
  // TODO: figure it out.
  int search(vector<int>& arr, int target)
  {
    int left = 0;
    int right = arr.size() - 1;

    while (left < right)
    {
      int mid = left + (right - left) / 2;  // 防止 left + right 过大

      // 左半数组升序
      if (arr[left] < arr[mid])
      {
        if (arr[left] <= target && target <= arr[mid])
        {
          // 目标在左半数组
          right = mid;
        }
        else
        {
          // 目标在右半数组
          left = mid + 1;
        }
      }

      // 右半数组升序
      else if (arr[left] > arr[mid])
      {
        if (arr[right] > target && target > arr[mid])
        {
          // 目标在右半数组
          left = mid + 1;
        }
        else
        {
          // 目标在左半数组
          right = mid;
        }
      }

      // 可能找到目标，也可能遇到重复值
      else
      {
        if (arr[left] != target)
        {
          left++;
        }
        else
        {
          right = left;
        }
      }
    }
    return (arr[left] == target) ? left : -1;
  }
};
