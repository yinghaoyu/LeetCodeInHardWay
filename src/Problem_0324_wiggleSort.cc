#include <iostream>
#include <type_traits>
#include <vector>

#include "UnitTest.h"

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  void wiggleSort(vector<int> &nums)
  {
    if (nums.size() < 2)
    {
      return;
    }
    int N = nums.size();
    findIndexNum(nums, 0, N - 1, N / 2);
    if (N & 1)
    {
      shuffle(nums, 1, N - 1);
    }
    else
    {
      shuffle(nums, 0, N - 1);
      reverse(nums, 0, N - 1);
    }
  }

  int findIndexNum(vector<int> &arr, int L, int R, int index)
  {
    int anchor = 0;
    vector<int> range;
    while (L < R)
    {
      anchor = arr[L];
      range = partition(arr, L, R, anchor);
      if (index >= range[0] && index <= range[1])
      {
        return arr[index];
      }
      else if (index < range[0])
      {
        R = range[0] - 1;
      }
      else
      {
        L = range[1] + 1;
      }
    }
    return arr[L];
  }

  vector<int> partition(vector<int> &arr, int L, int R, int anchor)
  {
    int less = L - 1;
    int more = R + 1;
    int cur = L;
    while (cur < more)
    {
      if (arr[cur] < anchor)
      {
        swap(arr, ++less, cur++);
      }
      else if (arr[cur] > anchor)
      {
        swap(arr, cur, --more);
      }
      else
      {
        cur++;
      }
    }
    return {less + 1, more - 1};
  }

  void shuffle(vector<int> &nums, int l, int r)
  {
    while (r - l + 1 > 0)
    {
      int lenAndOne = r - l + 2;
      int bloom = 3;
      int k = 1;
      while (bloom < lenAndOne / 3)
      {
        bloom *= 3;
        k++;
      }
      int m = (bloom - 1) / 2;
      int mid = (l + r) / 2;
      rotate(nums, l + m, mid, mid + m);
      cycles(nums, l - 1, bloom, k);
      l = l + bloom - 1;
    }
  }

  void cycles(vector<int> &nums, int base, int bloom, int k)
  {
    for (int i = 0, trigger = 1; i < k; i++, trigger *= 3)
    {
      int next = (2 * trigger) % bloom;
      int cur = next;
      int record = nums[next + base];
      int tmp = 0;
      nums[next + base] = nums[trigger + base];
      while (cur != trigger)
      {
        next = (2 * cur) % bloom;
        tmp = nums[next + base];
        nums[next + base] = record;
        cur = next;
        record = tmp;
      }
    }
  }

  void rotate(vector<int> &arr, int l, int m, int r)
  {
    reverse(arr, l, m);
    reverse(arr, m + 1, r);
    reverse(arr, l, r);
  }

  void reverse(vector<int> &arr, int l, int r)
  {
    while (l < r)
    {
      swap(arr, l++, r--);
    }
  }

  void swap(vector<int> &nums, int i, int j)
  {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
  }
};

void testWiggleSort()
{
  Solution s;
  vector<int> n1 = {1, 5, 1, 1, 6, 4};
  vector<int> n2 = {1, 3, 2, 2, 3, 1};
  vector<int> o1 = {1, 6, 1, 5, 1, 4};
  vector<int> o2 = {2, 3, 1, 3, 1, 2};
  s.wiggleSort(n1);
  s.wiggleSort(n2);
  EXPECT_TRUE(o1 == n1);
  EXPECT_TRUE(o2 == n2);
  EXPECT_SUMMARY;
}

int main()
{
  testWiggleSort();
  return 0;
}
