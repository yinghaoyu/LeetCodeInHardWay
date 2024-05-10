#include <vector>

using namespace std;

class Solution
{
 public:
  int countTestedDevices(vector<int>& batteryPercentages)
  {
    int n = batteryPercentages.size();
    int ans = 0;
    for (int p : batteryPercentages)
    {
      if (p > ans)
      {
        ans++;
      }
    }
    return ans;
  }
};
