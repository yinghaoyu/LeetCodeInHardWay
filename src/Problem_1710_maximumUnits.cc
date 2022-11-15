#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maximumUnits(vector<vector<int>> &boxTypes, int truckSize)
  {
    int ans = 0;
    std::sort(boxTypes.begin(), boxTypes.end(), [](vector<int> &a, vector<int> &b) { return a[1] > b[1]; });
    for (int i = 0; i < boxTypes.size(); i++)
    {
      // cout << boxTypes[i][0] << " " << boxTypes[i][1] << endl;
      if (truckSize - boxTypes[i][0] >= 0)
      {
        ans += boxTypes[i][0] * boxTypes[i][1];
        truckSize -= boxTypes[i][0];
      }
      else
      {
        ans += truckSize * boxTypes[i][1];
        truckSize -= truckSize;
        break;
      }
    }
    return ans;
  }
};

void testMaximumUnits()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 3}, {2, 2}, {3, 1}};
  vector<vector<int>> n2 = {{5, 10}, {2, 5}, {4, 7}, {3, 9}};
  EXPECT_EQ_INT(8, s.maximumUnits(n1, 4));
  EXPECT_EQ_INT(91, s.maximumUnits(n2, 10));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximumUnits();
  return 0;
}
