#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int rectangleArea(vector<vector<int>> &rectangles)
  {
    int ans = 0;
    // TODO: 线段树
    return ans % 1000000007;
  }
};

void testRectangleArea()
{
  Solution s;
  vector<vector<int>> arr1 = {{0, 0, 2, 2}, {1, 0, 2, 3}, {1, 0, 3, 1}};
  vector<vector<int>> arr2 = {{0, 0, 1000000000, 1000000000}};

  EXPECT_EQ_INT(6, s.rectangleArea(arr1));
  EXPECT_EQ_INT(49, s.rectangleArea(arr2));

  EXPECT_SUMMARY;
}

int main()
{
  testRectangleArea();
  return 0;
}
