#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool containsDuplicate1(vector<int> &nums)
  {
    if (nums.size() < 2)
    {
      return false;
    }
    heapSort(nums);
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i] == nums[i - 1])
      {
        return true;
      }
    }
    return false;
  }

  void heapSort(vector<int> &arr)
  {
    if (arr.size() < 2)
    {
      return;
    }
    for (int i = arr.size() - 1; i >= 0; i--)
    {
      heapify(arr, i, arr.size());
    }
    int heapSize = arr.size();
    swap(arr, 0, --heapSize);
    while (heapSize > 0)
    {
      heapify(arr, 0, heapSize);
      swap(arr, 0, --heapSize);
    }
  }

  // 往下调整
  void heapify(vector<int> &arr, int index, int heapSize)
  {
    // 因为下标从0开始，所以左孩子为 2 * index + 1
    int left = index * 2 + 1;
    while (left < heapSize)
    {
      int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
      largest = arr[largest] > arr[index] ? largest : index;
      if (largest == index)
      {
        break;
      }
      swap(arr, largest, index);
      index = largest;
      left = index * 2 + 1;
    }
  }

  void swap(vector<int> &arr, int i, int j)
  {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }

  bool containsDuplicate2(vector<int> &nums)
  {
    unordered_set<int> set;
    for (auto &num : nums)
    {
      if (set.count(num))
      {
        return true;
      }
      set.emplace(num);
    }
    return false;
  }
};

void testContainDuplicate()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 1};
  vector<int> n2 = {1, 2, 3, 4};
  vector<int> n3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
  EXPECT_TRUE(s.containsDuplicate1(n1));
  EXPECT_FALSE(s.containsDuplicate1(n2));
  EXPECT_TRUE(s.containsDuplicate1(n3));
  EXPECT_TRUE(s.containsDuplicate2(n1));
  EXPECT_FALSE(s.containsDuplicate2(n2));
  EXPECT_TRUE(s.containsDuplicate2(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testContainDuplicate();
  return 0;
}
