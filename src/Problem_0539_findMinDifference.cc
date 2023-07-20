#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int getMinutes(string &time) { return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0'); }

  int findMinDifference(vector<string> &timePoints)
  {
    if (timePoints.size() > 60 * 24)
    {
      return 0;
    }
    int ans = 60 * 24;
    std::sort(timePoints.begin(), timePoints.end());
    for (int i = 1; i < timePoints.size(); i++)
    {
      ans = std::min(ans, getMinutes(timePoints[i]) - getMinutes(timePoints[i - 1]));
    }
    ans = std::min(ans, getMinutes(timePoints.front()) - getMinutes(timePoints.back()) + 60 * 24);
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> t1 = {"23:59", "00:00"};
  vector<string> t2 = {"00:00", "23:59", "00:00"};
  EXPECT_EQ_INT(1, s.findMinDifference(t1));
  EXPECT_EQ_INT(0, s.findMinDifference(t2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
