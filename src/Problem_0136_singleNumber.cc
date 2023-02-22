#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int singleNumber(vector<int> &nums)
  {
    int ans = 0;
    for (auto &num : nums)
    {
      ans ^= num;
    }
    return ans;
  }
};

void testSingleNumber()
{
  Solution s;
  vector<int> n1 = {2, 2, 1};
  vector<int> n2 = {4, 1, 2, 1, 2};
  vector<int> n3 = {1};
  EXPECT_EQ_INT(1, s.singleNumber(n1));
  EXPECT_EQ_INT(4, s.singleNumber(n2));
  EXPECT_EQ_INT(1, s.singleNumber(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testSingleNumber();
  return 0;
}
