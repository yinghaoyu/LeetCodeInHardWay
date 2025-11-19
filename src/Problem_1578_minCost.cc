#include <string>
#include <vector>

using namespace std;

// 贪心
class Solution
{
 public:
  int minCost(string colors, vector<int>& neededTime)
  {
    int n = colors.length();
    int ans = 0;
    int i = 0;

    while (i < n)
    {
      char ch = colors[i];
      int maxTime = 0;
      int sum = 0;

      // 每组相同颜色的气球保留耗时最长的
      while (i < n && colors[i] == ch)
      {
        maxTime = std::max(maxTime, neededTime[i]);
        sum += neededTime[i];
        i++;
      }

      ans += sum - maxTime;
    }
    return ans;
  }
};
