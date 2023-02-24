#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> circularPermutation(int n, int start)
  {
    // TODO: figure it out
    vector<int> ret(1 << n);
    for (int i = 0; i < ret.size(); i++)
    {
      ret[i] = (i >> 1) ^ i ^ start;
    }
    return ret;
  };

  void testCircularPermutation()
  {
    Solution s;
    vector<int> o1 = {3, 2, 0, 1};
    vector<int> o2 = {2, 6, 7, 5, 4, 0, 1, 3};
    EXPECT_TRUE(o1 == s.circularPermutation(2, 3));
    EXPECT_TRUE(o2 == s.circularPermutation(3, 2));
    EXPECT_SUMMARY;
  }

  int main()
  {
    testCircularPermutation();
    return 0;
  }
