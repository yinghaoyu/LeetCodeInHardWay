#include <iostream>
#include <random>
#include <vector>

#include "UnitTest.h"

using namespace std;
class Solution
{
 public:
  int getRandom(int min, int max)
  {
    random_device seed;
    ranlux48 engine(seed());
    uniform_int_distribution<> distrib(min, max);
    int res = distrib(engine);
    return res;
  }

  void swap(vector<int> &arr, int i, int j)
  {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }

  vector<int> generateRandomArray(int maxSize, int maxValue)
  {
    int len = getRandom(1, maxSize);
    vector<int> arr(len);
    for (int i = 0; i < len; i++)
    {
      arr[i] = getRandom(1, maxValue + 1) - getRandom(0, maxValue);
    }
    return arr;
  }

  // 群友的写法
  int partition(vector<int> &nums, int left, int right)
  {
    int pivot = nums[left];
    int i = left;
    int j = right;
    while (i < j)
    {
      while (i < j && nums[j] >= pivot)
        j--;
      while (i < j && nums[i] <= pivot)
        i++;

      if (i < j)
        std::swap(nums[i], nums[j]);
    }
    nums[left] = nums[i];
    nums[i] = pivot;

    return i;
  }

  int findKthLargest1(vector<int> &nums, int k)
  {
    int n = nums.size();
    int left = 0;
    int right = n - 1;
    int target = n - k;
    while (true)
    {
      int index = partition(nums, left, right);
      if (index == target)
        return nums[index];
      else if (index < target)
        left = index + 1;
      else
      {
        right = index - 1;
      }
    }
  }

  // 我的写法
  vector<int> partition(vector<int> &arr, int L, int R, int pivot)
  {
    int less = L - 1;
    int more = R + 1;
    int cur = L;
    while (cur < more)
    {
      if (arr[cur] < pivot)
      {
        swap(arr, ++less, cur++);
      }
      else if (arr[cur] > pivot)
      {
        swap(arr, cur, --more);
      }
      else
      {
        cur++;
      }
    }
    return {less + 1, more - 1};  // 这个范围的数是等于pivot的数
  }

  int process(vector<int> &arr, int L, int R, int index)
  {
    if (L == R)
    {
      // L == R ==INDEX
      return arr[L];
    }
    // 不止一个数  L +  [0, R -L]
    int pivot = arr[L + getRandom(0, R - L + 1)];
    vector<int> range = partition(arr, L, R, pivot);  // range 返回的是等于pivot的区间
    if (index >= range[0] && index <= range[1])       // 长度在区间内
    {
      return arr[index];
    }
    else if (index < range[0])  // 小于这个区间，就从左半区找
    {
      return process(arr, L, range[0] - 1, index);
    }
    else  // 大于这个区间就从右半区找
    {
      return process(arr, range[1] + 1, R, index);
    }
  }

  int findKthLargest2(vector<int> &nums, int k) { return process(nums, 0, nums.size() - 1, nums.size() - k); }
};

void testFindKthLargest()
{
  Solution s;
  int testTime = 500000;
  int maxSize = 20;
  int maxValue = 100;
  bool succeed = true;
  for (int i = 0; i < testTime; i++)
  {
    vector<int> arr1 = s.generateRandomArray(maxSize, maxValue);
    vector<int> arr2 = arr1;
    vector<int> arr3 = arr1;
    int k = s.getRandom(1, arr1.size());
    int a = s.findKthLargest1(arr1, k);
    int b = s.findKthLargest2(arr2, k);
    EXPECT_EQ_INT(a, b);
  }
  EXPECT_SUMMARY;
}

int main()
{
  testFindKthLargest();
  return 0;
}
