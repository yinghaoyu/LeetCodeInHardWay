#include <vector>
#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int gcd(int a, int b) { return b > 0 ? gcd(b, a % b) : a; }

  bool isGoodArray(vector<int> &nums)
  {
    // TODO: figure it out
    int divisor = nums[0];
    for (int num : nums)
    {
      divisor = gcd(divisor, num);
      if (divisor == 1)
      {
        break;
      }
    }
    return divisor == 1;
  }
};

void testIsGoodArray()
{
  Solution s;
  vector<int> n1 = {12, 5, 7, 23};
  vector<int> n2 = {29, 6, 10};
  vector<int> n3 = {3, 6};
  EXPECT_TRUE(s.isGoodArray(n1));
  EXPECT_TRUE(s.isGoodArray(n2));
  EXPECT_FALSE(s.isGoodArray(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testIsGoodArray();
  return 0;
}
