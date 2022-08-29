#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> shuffle(vector<int> &nums, int n)
  {
    vector<int> ans(nums.size());
    for (int i = 0, j = 0, k = n; i < nums.size(); i++)
    {
      ans[i] = i & 1 ? nums[k++] : nums[j++];
    }
    return ans;
  }
};

bool isEqualVector(vector<int> arr1, vector<int> arr2)
{
  if (arr1.size() != arr2.size())
  {
    return false;
  }
  for (int i = 0; i < arr1.size(); i++)
  {
    if (arr1[i] != arr2[i])
    {
      return false;
    }
  }
  return true;
}

void testShuffle()
{
  Solution s;
  vector<int> arr1 = {2, 5, 1, 3, 4, 7};
  vector<int> out1 = {2, 3, 5, 4, 1, 7};
  int n1 = 3;

  vector<int> arr2 = {1, 2, 3, 4, 4, 3, 2, 1};
  vector<int> out2 = {1, 4, 2, 3, 3, 2, 4, 1};
  int n2 = 4;

  EXPECT_TRUE(isEqualVector(s.shuffle(arr1, n1), out1));
  EXPECT_TRUE(isEqualVector(s.shuffle(arr2, n2), out2));
  EXPECT_SUMMARY;
}

int main()
{
  testShuffle();
  return 0;
}
