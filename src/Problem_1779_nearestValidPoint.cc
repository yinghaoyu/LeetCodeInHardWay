#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int nearestValidPoint(int x, int y, vector<vector<int>> &points)
  {
    int min = INT32_MAX;
    int index = -1;
    int n = points.size();
    for (int i = 0; i < n; i++)
    {
      int a = points[i][0];
      int b = points[i][1];
      if (x != a && y != b)
      {
        continue;
      }
      int d = std::abs(x - a) + std::abs(y - b);
      if (d < min)
      {
        min = d;
        index = i;
      }
    }
    return index;
  }
};

void testNearestValidPoint()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 2}, {3, 1}, {2, 4}, {2, 3}, {4, 4}};
  vector<vector<int>> n2 = {{3, 4}};
  vector<vector<int>> n3 = {{2, 3}};
  EXPECT_EQ_INT(2, s.nearestValidPoint(3, 4, n1));
  EXPECT_EQ_INT(0, s.nearestValidPoint(3, 4, n2));
  EXPECT_EQ_INT(-1, s.nearestValidPoint(3, 4, n3));
  EXPECT_SUMMARY;
}

int main()
{
  testNearestValidPoint();
  return 0;
}
