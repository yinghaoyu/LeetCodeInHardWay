#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool check(vector<int> &nums)
  {
    int cnt = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      if (nums[i] > nums[(i + 1) % n])
      {
        cnt++;
      }
    }
    return cnt <= 1;
  }
};

void testCheck()
{
  Solution s;
  vector<int> n1 = {3, 4, 5, 1, 2};
  vector<int> n2 = {1, 2, 3, 4, 5};
  vector<int> n3 = {2, 3, 4, 1, 5};
  EXPECT_TRUE(s.check(n1));
  EXPECT_TRUE(s.check(n2));
  EXPECT_FALSE(s.check(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testCheck();
  return 0;
}
