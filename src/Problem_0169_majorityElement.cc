#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int majorityElement(vector<int> &nums)
  {
    int blood = 0;
    int solider = 0;
    for (auto &num : nums)
    {
      if (blood == 0)
      {
        solider = num;
        blood++;
      }
      else
      {
        blood += num == solider ? 1 : -1;
      }
    }
    return solider;
  }
};

void testMajorityElement()
{
  Solution s;
  vector<int> n1 = {3, 2, 3};
  vector<int> n2 = {2, 2, 1, 1, 1, 2, 2};
  EXPECT_EQ_INT(3, s.majorityElement(n1));
  EXPECT_EQ_INT(2, s.majorityElement(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testMajorityElement();
  return 0;
}
