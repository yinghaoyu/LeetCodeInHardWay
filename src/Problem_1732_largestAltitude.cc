#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int largestAltitude(vector<int> &gain)
  {
    int n = gain.size();
    int max = 0;
    int start = 0;
    for (int i = 0; i < n; i++)
    {
      start += gain[i];
      max = std::max(max, start);
    }
    return max;
  }
};

void testLargestAltitude()
{
  Solution s;
  vector<int> n1 = {-5, 1, 5, 0, -7};
  vector<int> n2 = {-4, -3, -2, -1, 4, 3, 2};
  EXPECT_EQ_INT(1, s.largestAltitude(n1));
  EXPECT_EQ_INT(0, s.largestAltitude(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testLargestAltitude();
  return 0;
}
