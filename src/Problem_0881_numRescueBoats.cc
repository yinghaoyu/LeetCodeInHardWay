#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 贪心算法
  // 时间复杂度O(N*logN)，因为有排序，额外空间复杂度O(1)
  int numRescueBoats(vector<int>& people, int limit)
  {
    std::sort(people.begin(), people.end());
    int ans = 0;
    int l = 0;
    int r = people.size() - 1;
    int sum = 0;
    while (l <= r)
    {
      sum = l == r ? people[l] : people[l] + people[r];
      if (sum > limit)
      {
        // 重量已从小打大排序，尽量单独载更重的，
        // 这样的话，比较容易凑出两个人坐一只船
        r--;
      }
      else
      {
        l++;
        r--;
      }
      ans++;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> p1 = {1, 2};
  vector<int> p2 = {3, 2, 2, 1};
  vector<int> p3 = {3, 5, 3, 4};
  EXPECT_EQ_INT(1, s.numRescueBoats(p1, 3));
  EXPECT_EQ_INT(3, s.numRescueBoats(p2, 3));
  EXPECT_EQ_INT(4, s.numRescueBoats(p3, 5));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
