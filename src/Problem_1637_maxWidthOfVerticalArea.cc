#include <iostream>
#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxWidthOfVerticalArea(vector<vector<int>> &points)
  {
    std::sort(points.begin(), points.end(), [](vector<int>&a, vector<int>&b){ return a[0] < b[0]; });
    int N = points.size();
    int max = 0;
    for (int i = 1; i < N; i++)
    {
      max = std::max(max, points[i][0] - points[i - 1][0]);
    }
    return max;
  }
};

void testMaxWidthOfVerticalArea()
{
  Solution s;
  vector<vector<int>> n1 = {{8, 7}, {9, 9}, {7, 4}, {9, 7}};
  vector<vector<int>> n2 = {{3, 1}, {9, 0}, {1, 0}, {1, 4}, {5, 3}, {8, 8}};
  EXPECT_EQ_INT(1, s.maxWidthOfVerticalArea(n1));
  EXPECT_EQ_INT(3, s.maxWidthOfVerticalArea(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxWidthOfVerticalArea();
  return 0;
}
