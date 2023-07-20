#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  int getMinutes(string &time) { return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0'); }

  int findMinDifference(vector<string> &timePoints)
  {
    if (timePoints.size() > 60 * 24)
    {
      // 鸽巢原理(抽屉原理)
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
