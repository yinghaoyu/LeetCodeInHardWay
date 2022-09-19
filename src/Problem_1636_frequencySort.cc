#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> frequencySort(vector<int> &nums)
  {
    unordered_map<int, int> cnt;
    for (int num : nums)
    {
      cnt[num]++;
    }
    std::sort(nums.begin(), nums.end(), [&](const int a, const int b) { return cnt[a] < cnt[b] || (cnt[a] == cnt[b] && a > b); });
    return nums;
  }
};

bool isVectorEqual(const vector<int> &l, const vector<int> &r)
{
  if (l.size() != r.size())
  {
    return false;
  }
  for (int i = 0; i < l.size(); i++)
  {
    if (l[i] != r[i])
    {
      return false;
    }
  }
  return true;
}

void testFrequencySort()
{
  Solution s;
  vector<int> nums1 = {1, 1, 2, 2, 2, 3};
  vector<int> arr1 = {3, 1, 1, 2, 2, 2};
  vector<int> nums2 = {2, 3, 1, 3, 2};
  vector<int> arr2 = {1, 3, 3, 2, 2};
  vector<int> nums3 = {-1, 1, -6, 4, 5, -6, 1, 4, 1};
  vector<int> arr3 = {5, -1, 4, 4, -6, -6, 1, 1, 1};
  EXPECT_TRUE(isVectorEqual(arr1, s.frequencySort(nums1)));
  EXPECT_TRUE(isVectorEqual(arr2, s.frequencySort(nums2)));
  EXPECT_TRUE(isVectorEqual(arr3, s.frequencySort(nums3)));
  EXPECT_SUMMARY;
}

int main()
{
  testFrequencySort();
  return 0;
}
