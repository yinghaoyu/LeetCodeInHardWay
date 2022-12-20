#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> twoSum(vector<int> &nums, int target)
  {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++)
    {
      if (map.count(target - nums[i]))
      {
        return {map[target - nums[i]], i};
      }
      map[nums[i]] = i;
    }
    return {-1, -1};
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  return a == b;
}

void testTwoSum()
{
  Solution s;
  vector<int> n1 = {2, 7, 11, 15};
  vector<int> n2 = {3, 2, 4};
  vector<int> n3 = {3, 3};
  EXPECT_TRUE(isVectorEqual({0, 1}, s.twoSum(n1, 9)));
  EXPECT_TRUE(isVectorEqual({1, 2}, s.twoSum(n2, 6)));
  EXPECT_TRUE(isVectorEqual({0, 1}, s.twoSum(n3, 6)));
  EXPECT_SUMMARY;
}

int main()
{
  testTwoSum();
  return 0;
}
