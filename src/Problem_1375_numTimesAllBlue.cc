#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numTimesAllBlue(vector<int> &flips)
  {
    int n = flips.size();
    int right = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      right = std::max(right, flips[i]);
      if (right == i + 1)
      {
        ans++;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> f1 = {3, 2, 4, 1, 5};
  vector<int> f2 = {4, 1, 2, 3};
  EXPECT_EQ_INT(2, s.numTimesAllBlue(f1));
  EXPECT_EQ_INT(1, s.numTimesAllBlue(f2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
