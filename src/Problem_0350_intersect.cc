#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
  {
    unordered_map<int, int> map1;
    for (int num : nums1)
    {
      if (!map1.count(num))
      {
        map1.emplace(num, 1);
      }
      else
      {
        map1[num]++;
      }
    }
    unordered_map<int, int> map2;
    for (int num : nums2)
    {
      if (!map2.count(num))
      {
        map2.emplace(num, 1);
      }
      else
      {
        map2[num]++;
      }
    }
    vector<int> ans;
    for (auto &[key, _] : map1)
    {
      if (map2.count(key))
      {
        int n = std::min(map1.at(key), map2.at(key));
        for (int i = 0; i < n; i++)
        {
          ans.push_back(key);
        }
      }
    }
    return ans;
  }
};

void testIntersect()
{
  Solution s;
  vector<int> n1 = {1, 2, 2, 1};
  vector<int> n2 = {2, 2};
  vector<int> n3 = {4, 9, 5};
  vector<int> n4 = {9, 4, 9, 8, 4};
  vector<int> o1 = {2, 2};
  vector<int> o2 = {9, 4};
  EXPECT_TRUE(o1 == s.intersect(n1, n2));
  EXPECT_TRUE(o2 == s.intersect(n3, n4));
  EXPECT_SUMMARY;
}

int main()
{
  testIntersect();
  return 0;
}
