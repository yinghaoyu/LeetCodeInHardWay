#include <vector>

using namespace std;

class Solution
{
 public:
  int tendency(int a, int b)
  {
    if (a == b)
    {
      return 0;
    }
    return a < b ? -1 : 1;
  }

  int temperatureTrend(vector<int>& temperatureA, vector<int>& temperatureB)
  {
    int n = temperatureA.size();
    int ans = 0;
    int cur = 0;
    for (int i = 1; i < n; i++)
    {
      int ta = tendency(temperatureA[i], temperatureA[i - 1]);
      int tb = tendency(temperatureB[i], temperatureB[i - 1]);
      if (ta == tb)
      {
        cur++;
        ans = std::max(ans, cur);
      }
      else
      {
        cur = 0;
      }
    }
    return ans;
  }
};
