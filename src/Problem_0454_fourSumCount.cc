#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
  {
    unordered_map<int, int> map;
    int sum = 0;
    for (int i = 0; i < nums1.size(); i++)
    {
      for (int j = 0; j < nums2.size(); j++)
      {
        sum = nums1[i] + nums2[j];
        if (!map.count(sum))
        {
          map.emplace(sum, 1);
        }
        else
        {
          map[sum]++;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < nums3.size(); i++)
    {
      for (int j = 0; j < nums4.size(); j++)
      {
        sum = nums3[i] + nums4[j];
        if (map.count(-sum))
        {
          ans += map.at(-sum);
        }
      }
    }
    return ans;
  }
};

void testFourSumCount()
{
  Solution s;
  vector<int> n1 = {1, 2};
  vector<int> n2 = {-2, -1};
  vector<int> n3 = {-1, 2};
  vector<int> n4 = {0, 2};

  vector<int> m1 = {0};
  vector<int> m2 = {0};
  vector<int> m3 = {0};
  vector<int> m4 = {0};
  EXPECT_EQ_INT(2, s.fourSumCount(n1, n2, n3, n4));
  EXPECT_EQ_INT(1, s.fourSumCount(m1, m2, m3, m4));
  EXPECT_SUMMARY;
}

int main()
{
  testFourSumCount();
  return 0;
}
