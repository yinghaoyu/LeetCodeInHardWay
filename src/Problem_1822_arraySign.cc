#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int arraySign(vector<int> &nums)
  {
    int neg = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      if (nums[i] == 0)
      {
        return 0;
      }
      neg += nums[i] < 0 ? 1 : 0;
    }
    return neg & 1 ? -1 : 1;
  }
};

void testArraySign()
{
  Solution s;
  vector<int> n1 = {-1, -2, -3, -4, 3, 2, 1};
  vector<int> n2 = {1, 5, 0, 2, -3};
  vector<int> n3 = {-1, 1, -1, 1, -1};
  EXPECT_EQ_INT(1, s.arraySign(n1));
  EXPECT_EQ_INT(0, s.arraySign(n2));
  EXPECT_EQ_INT(-1, s.arraySign(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testArraySign();
  return 0;
}
