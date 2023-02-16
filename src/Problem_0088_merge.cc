#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
  {
    int index = nums1.size();
    while (m > 0 && n > 0)
    {
      if (nums1[m - 1] > nums2[n - 1])
      {
        nums1[--index] = nums1[--m];
      }
      else
      {
        nums1[--index] = nums2[--n];
      }
    }
    while (m > 0)
    {
      nums1[--index] = nums1[--m];
    }
    while (n > 0)
    {
      nums1[--index] = nums2[--n];
    }
  }
};

void testMerge()
{
  Solution s;
  vector<int> v1 = {1, 2, 3, 0, 0, 0};
  vector<int> v2 = {2, 5, 6};
  vector<int> v3 = {1, 2, 2, 3, 5, 6};

  vector<int> v4 = {1};
  vector<int> v5 = {};
  vector<int> v6 = {1};

  vector<int> v7 = {0};
  vector<int> v8 = {1};
  vector<int> v9 = {1};

  s.merge(v1, 3, v2, 3);
  s.merge(v4, 1, v5, 0);
  s.merge(v7, 0, v8, 1);

  EXPECT_TRUE(v1 == v3);
  EXPECT_TRUE(v4 == v6);
  EXPECT_TRUE(v7 == v8);
  EXPECT_SUMMARY;
}

int main()
{
  testMerge();
  return 0;
}
